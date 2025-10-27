#include "parsing.h"

/*
and_or:			pipeline { "&&" | "||" pipeline }
pipeline:		command { "|" command }
command:		simple_command | subshell
simple_command:	WORD { WORD }
subshell:		"(" and_or ")"
*/

t_btree	*parse_and_or(t_list **tokens, t_here_doc **here_list);

t_list	*consume_token(t_list **tokens)
{
	t_list	*cur;

	cur = *tokens;
	if (cur)
		*tokens =  cur->next;
	return (cur);
}

t_btree	*make_bnode(t_bnode_type type, t_btree *left, t_btree *right)
{
	t_btree	*node;

	node = malloc(sizeof(t_btree));
	if (!node)
		return (palloc_err(), NULL);
	node->cmd_argv = NULL;
	node->redir_list = NULL;
	node->type = type;
	node->left = left;
	node->right = right;
	node->ambig = NULL;
	node->empty_cmd = 0;
	return (node);
}

int	store_words(t_list **tokens, char **cmd_argv)
{
	t_list	*cur;
	size_t	word_count;
	char	*word;

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
		word = ft_strdup(cur->token->str);
		if (!word)
		{
			cmd_argv[word_count] = NULL;
			return (free_split(cmd_argv), 1);
		}
		cmd_argv[word_count++] = word;
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

t_btree	*parse_command_args(t_list **tokens, t_here_doc **here_list)
{
	t_list	*cur;
	t_btree	*bnode;

	cur = *tokens;
	bnode = make_bnode(BNODE_COMMAND, NULL, NULL);
	if (!bnode)
		return (ft_printf(2, "malloc failed in make_bnode(): parse_command()\n"), NULL);
	bnode->cmd_argv = create_cmd_argv(tokens);
	if (!bnode->cmd_argv)
		return (ft_printf(2, "malloc failed in create_cmd_argv()\n"), NULL);
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

t_btree	*parse_command(t_list **tokens, t_here_doc **here_list)
{
	t_list	*cur;
	t_btree	*bnode;

	cur = *tokens;
	if (!cur)
		return (NULL);
	if (cur->token->options & OPEN_PARENTHESIS)
	{
		consume_token(tokens);
		bnode = parse_and_or(tokens, here_list);
		cur = *tokens;
		if (!cur || !(cur->token->options & CLOSE_PARENTHESIS))
			return (ft_printf(2, "Error: Expected `)'\n"), NULL);
		consume_token(tokens);
		return (make_bnode(BNODE_SUBSHELL, bnode, NULL));
	}
	else if (cur->token->options & WORD || cur->token->options & REDIR_OP)
		return (parse_command_args(tokens, here_list));
	return (ft_printf(2, "Error: Unexpected token\n"), NULL);
}

t_btree	*parse_pipeline(t_list **tokens, t_here_doc **here_list)
{
	t_btree	*left;
	t_btree	*right;

	left = parse_command(tokens, here_list);
	while (*tokens && (*tokens)->token->options & PIPE)
	{
		consume_token(tokens);
		right = parse_command(tokens, here_list);
		left = make_bnode(BNODE_PIPE, left, right);
	}
	return (left);
}

t_btree	*parse_and_or(t_list **tokens, t_here_doc **here_list)
{
	t_btree	*left;
	t_btree	*right;
	t_list	*cur;

	left = parse_pipeline(tokens, here_list);
	while ((*tokens)
		&& ((*tokens)->token->options & AND || (*tokens)->token->options & OR))
	{
		cur = *tokens;
		consume_token(tokens);
		right = parse_pipeline(tokens, here_list);
		if (cur->token->options & AND)
			left = make_bnode(BNODE_AND, left, right);
		else if (cur->token->options & OR)
			left = make_bnode(BNODE_OR, left, right);
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

// BIG ISSUE FOUND: WHAT HAPPENS WHEN MALLOC FAILS DEEP INSIDE ONE OF THESE FUNCTIONS?? YOU RETURN NULL, WHICH IS A VALID RETURN VALUE??
t_btree	*create_exec_tree(t_parse_data *d)
{
	t_btree	*tree;
	t_list	*tokens;

	tokens = d->tokens;
	tree = parse_and_or(&tokens, &d->here_list);
	if (open_write_here_docs(&d->here_list, d))
		return (printf("run_here_doc() failed\n"), NULL);
	// for (t_here_doc *cur = d->here_list; cur; cur = cur->next)
	// 	printf("HERE_DOC: file_name:(%s) == delimiter:(%s)\n", cur->file_name, cur->delimiter);
	// btree_apply_prefix(tree, print_redirs);
	return (tree);
}
