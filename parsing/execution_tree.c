#include "parsing.h"

/*
and_or:			pipeline { "&&" | "||" pipeline }
pipeline:		command { "|" command }
command:		simple_command | subshell
simple_command:	WORD { WORD }
subshell:		"(" and_or ")"
*/

t_btree	*parse_and_or(t_list **tokens, t_here_doc **here_list, int *flag);

t_list	*consume_token(t_list **tokens)
{
	t_list	*cur;

	cur = *tokens;
	if (cur)
		*tokens =  cur->next;
	return (cur);
}

t_btree	*make_bnode(t_bnode_type type, t_btree *left, t_btree *right, int *flag)
{
	t_btree	*node;

	node = malloc(sizeof(t_btree));
	if (!node)
	{
		*flag = -1;
		return (palloc_err(), left);
	}
	node->cmd_argv = NULL;
	node->redir_list = NULL;
	node->type = type;
	node->left = left;
	node->right = right;
	node->ambig = NULL;
	node->empty_cmd = 0;
	return (node);
}

int	dup_append_str(char **cmd_argv, char *str, size_t *word_count)
{
	char	*word;

	word = ft_strdup(str);
	if (!word)
	{
		cmd_argv[*word_count] = NULL;
		return (free_split(cmd_argv), 1);
	}
	cmd_argv[(*word_count)++] = word;
	return (0);
}

int	store_words(t_list **tokens, char **cmd_argv)
{
	t_list	*cur;
	size_t	word_count;

	cur = *tokens;
	word_count = 0;
	while (cur && (cur->token->options & WORD || cur->token->options & REDIR_OP))
	{
		if (cur->token->options & EMPTY_WORD || cur->token->options & REDIR_WORD)
		{
			cur = cur->next;
			continue ;
		}
		if (cur->token->options & REDIR_OP)
		{
			cur = cur->next->next;
			continue ;
		}
		if (dup_append_str(cmd_argv, cur->token->str, &word_count))
			return (1);
		cur = cur->next;
	}
	cmd_argv[word_count] = NULL;
	return (0);
}

char	**create_cmd_argv(t_list **tokens)
{
	t_list	*cur;
	size_t	word_count;
	char	**cmd_argv;

	word_count = 0;
	cur = *tokens;
	while (cur && (cur->token->options & WORD || cur->token->options & REDIR_OP))
	{
		if (cur->token->options & REDIR_OP || cur->token->options & REDIR_WORD
			|| cur->token->options & HERE_DEL_WORD)
			cur = cur->next;
		else if (!(cur->token->options & EMPTY_WORD))
			word_count++;
		cur = cur->next;
	}
	cmd_argv = malloc(sizeof(char *) * (word_count + 1));
	if (!cmd_argv)
		return (NULL);
	if (store_words(tokens, cmd_argv))
		return (ft_printf(2, "malloc failed in store_words()\n"), NULL);
	return (cmd_argv);
}

t_btree	*parse_command_args(t_list **tokens, t_here_doc **here_list, int *flag)
{
	t_list	*cur;
	t_btree	*bnode;

	cur = *tokens;
	bnode = make_bnode(BNODE_COMMAND, NULL, NULL, flag);
	if (!bnode)
		return (ft_printf(2, "malloc failed in make_bnode(): parse_command()\n"), NULL);
	bnode->cmd_argv = create_cmd_argv(tokens);
	if (!bnode->cmd_argv)
		return (ft_printf(2, "malloc failed in create_cmd_argv()\n"), delete_bnode(bnode), NULL);
	if (bnode->cmd_argv[0] == NULL)
		bnode->empty_cmd = 1;
	if (create_redirections(tokens, bnode, here_list))
		return (ft_printf(2, "create_redirections() failed\n"), free_split(bnode->cmd_argv), NULL);
	while (cur && (cur->token->options & WORD || cur->token->options & REDIR_OP))
	{
		cur = cur->next;
		consume_token(tokens);
	}
	return (bnode);
}

t_btree	*parse_command(t_list **tokens, t_here_doc **here_list, int *flag)
{
	t_list	*cur;
	t_btree	*bnode;

	cur = *tokens;
	if (!cur)
		return (NULL);
	if (cur->token->options & OPEN_PARENTHESIS)
	{
		consume_token(tokens);
		bnode = parse_and_or(tokens, here_list, flag);
		if (!bnode)
			return (NULL);
		cur = *tokens;
		if (!cur || !(cur->token->options & CLOSE_PARENTHESIS))
			return (ft_printf(2, "Error: Expected `)'\n"), NULL);
		consume_token(tokens);
		return (make_bnode(BNODE_SUBSHELL, bnode, NULL, flag));
	}
	else if (cur->token->options & WORD || cur->token->options & REDIR_OP)
		return (parse_command_args(tokens, here_list, flag));
	return (ft_printf(2, "Error: Unexpected token\n"), NULL);
}

t_btree	*parse_pipeline(t_list **tokens, t_here_doc **here_list, int *flag)
{
	t_btree	*left;
	t_btree	*right;

	right = NULL;
	left = parse_command(tokens, here_list, flag);
	if (flag)
		return (left);
	while (*tokens && (*tokens)->token->options & PIPE)
	{
		consume_token(tokens);
		right = parse_command(tokens, here_list, flag);
		if (flag)
			return (left);
		left = make_bnode(BNODE_PIPE, left, right, flag);
		if (!left)
			return (NULL);
	}
	return (left);
}

t_btree	*parse_and_or(t_list **tokens, t_here_doc **here_list, int *flag)
{
	t_btree	*left;
	t_btree	*right;
	t_list	*cur;

	right = NULL;
	left = parse_pipeline(tokens, here_list, flag);
	if (flag == -1)
		return (left);
	while ((*tokens)
		&& ((*tokens)->token->options & AND || (*tokens)->token->options & OR))
	{
		cur = *tokens;
		consume_token(tokens);
		right = parse_pipeline(tokens, here_list, flag);
		if (flag)
			return (left);
		if (cur->token->options & AND)
			left = make_bnode(BNODE_AND, left, right, flag);
		else if (cur->token->options & OR)
		{

			left = make_bnode(BNODE_OR, left, right, flag);
		}
		if ((cur->token->options & AND & OR) && !left)
			return (NULL);	
	}
	return (left);
}

void	print_redirs(void *ptr)
{
	t_btree	*node;

	node = (t_btree *)ptr;
	if (node->type == BNODE_COMMAND)
	{
		printf("trying to printf list of redirs for node (%s):\n", node->cmd_argv[0]);
		for (t_redir_list *cur = node->redir_list; cur; cur = cur->next)
			printf("file_name:(%s)\n", cur->file_name);
		clear_redir_list(&node->redir_list);
	}
}

t_btree	*create_exec_tree(t_parse_data *d)
{
	t_btree	*tree;
	int 	flag;
	t_list	*tokens;

	flag = 0;
	tokens = d->tokens;
	tree = parse_and_or(&tokens, &d->here_list, &flag);
	// printf("head: (%p) tree (%p)\n", head, tree);
	if (flag)
		return (btree_apply_suffix(tree, delete_bnode), NULL);
	if (open_write_here_docs(&d->here_list, d))
		return (printf("run_here_doc() failed\n"), NULL);
	// for (t_here_doc *cur = d->here_list; cur; cur = cur->next)
	// 	printf("HERE_DOC: file_name:(%s) == delimiter:(%s)\n", cur->file_name, cur->delimiter);
	// btree_apply_prefix(tree, print_redirs);
	return (tree);
}
