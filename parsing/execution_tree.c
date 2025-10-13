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
		return (ft_printf(2, "malloc fail in make_bnode()\n"), NULL);
	node->cmd_argv = NULL;
	node->redir.append = 0;
	node->redir.in = NULL;
	node->redir.out = NULL;
	node->type = type;
	node->left = left;
	node->right = right;
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
		if (cur->token->options & EMPTY_WORD)
		{
			cur = cur->next;
			consume_token(tokens);
			continue ;
		}
		if (cur->token->options & REDIR_OP)
		{
			cur = cur->next->next; // MAYBE WE CAN HANDLE AMBIGUOUS REDIRECTIONS HERE??
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
		consume_token(tokens);
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
		if (cur->token->options & REDIR_OP)
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

int	add_here_node(t_here_doc **here_list, char *delimiter, t_btree *bnode)
{
	t_here_doc	*here_node;
	t_here_doc	*cur;

	here_node = malloc(sizeof(t_here_doc));
	if (!here_node)
		return (1);
	here_node->bnode = bnode;
	here_node->delimiter = ft_strdup(delimiter);
	if (here_node->delimiter)
		return (free(here_node), 1);
	here_node->next = NULL;
	if (!*here_list)
		*here_list = here_node;
	else
	{
		cur = *here_list;
		while (cur->next)
			cur = cur->next;
		cur->next = here_node;
	}
	return (0);
}

int glob_i = 0;
int	create_redirections(t_list **tokens, t_btree *node, t_here_doc **here_list)
{
	t_list	*cur;

	cur = *tokens;
	node->redir.in = NULL;
	node->redir.out = NULL;
	node->redir.append = 0;
	while (cur && (cur->token->options & WORD || cur->token->options & REDIR_OP))
	{
		if (cur->token->options & REDIR_OP)
		{
			if (cur->token->options & HERE_DOC)
			{
				if (add_here_node(here_list, cur->next->token->str, node))
					return (1);
			}
			else if (cur->token->options & OUTPUT_REDIR_APPEND)
			{
				node->redir.append = 1;
				free(node->redir.out);
				node->redir.out = ft_strdup(cur->next->token->str);
				if (!node->redir.out)
					return (free(node->redir.in), 1);
			}
			else if (cur->token->options & INPUT_REDIR)
			{
				free(node->redir.in);
				node->redir.in = ft_strdup(cur->next->token->str);
				if (!node->redir.in)
					return (free(node->redir.out), 1);
			}
			else if (cur->token->options & OUTPUT_REDIR)
			{
				free(node->redir.out);
				node->redir.out = ft_strdup(cur->next->token->str);
				if (!node->redir.out)
					return (free(node->redir.in), 1);
			}
			cur = cur->next;
			consume_token(tokens);
		}
		cur = cur->next;
		consume_token(tokens);
	}
	// printf("for node (%s), redirect input to (%s) and output to (%s)\n", node->cmd_argv[0], node->redir.in, node->redir.out);
	return (0);
}

t_btree	*parse_command(t_list **tokens, t_here_doc **here_list)
{
	t_list	*cur;
	t_btree	*node;

	cur = *tokens;
	if (!cur)
		return (NULL);
	if (cur->token->options & OPEN_PARENTHESIS)
	{
		consume_token(tokens);
		node = parse_and_or(tokens, here_list);
		cur = *tokens;
		if (!cur || !(cur->token->options & CLOSE_PARENTHESIS))
			return (ft_printf(2, "Error: Expected `)'\n"), NULL);
		consume_token(tokens);
		return (make_bnode(BNODE_SUBSHELL, node, NULL));
	}
	else if (cur->token->options & WORD || cur->token->options & REDIR_OP)
	{
		node = make_bnode(BNODE_COMMAND, NULL, NULL);
		if (!node)
			return (ft_printf(2, "malloc failed in make_bnode(): parse_command()\n"), NULL);
		node->cmd_argv = create_cmd_argv(tokens);
		if (!node->cmd_argv)
			return (ft_printf(2, "malloc failed in create_cmd_argv()\n"), NULL);
		if (create_redirections(tokens, node, here_list))
			return (ft_printf(2, "create_redirections() failed\n"), free_split(node->cmd_argv), NULL);
		return (node);
	}
	return (ft_printf(2, "Error: Unexpected token\n"), NULL);
}

t_btree	*parse_pipeline(t_list **tokens, t_here_doc **here_list)
{
	t_btree	*left;
	t_btree	*right;
	t_list	*cur;

	left = parse_command(tokens, here_list);
	while (*tokens && (*tokens)->token->options & PIPE)
	{
		cur = *tokens;
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

int	open_here_docs(t_here_doc *here_list, int *line_count)
{
	t_here_doc	*cur;
	char		*line;
	int			here_fd;

	cur = here_list;
	here_fd = open(, O_WRONLY | O_CREAT | O_EXCL, 0666); // Maybe change file name because of confilcts (is ".tmp" a common name?).
	while (cur)
	{
		while (1)
		{
			line = readline(">");
			if (!line)
			{
				ft_printf(2, "bash: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", *line_count, cur->delimiter);
				break ;
			}
			*line_count += 1;
		}
	}
}

// BIG ISSUE FOUND: WHAT HAPPENS WHEN MALLOC FAILS DEEP INSIDE ONE OF THESE FUNCTIONS?? YOU RETURN NULL, WHICH IS A VALID RETURN VALUE??

t_btree	*create_tree(t_list *tokens, int *line_count)
{
	t_btree		*tree;
	t_here_doc	*here_list;

	here_list = NULL;
	tree = parse_and_or(&tokens, &here_list);
	if (open_here_docs(&here_list, line_count))
		return (printf("run_here_doc() failed\n"), NULL);
	// printf("redirect input to (%s) and output to (%s)\n", tree->redir.in, tree->redir.out);
	return (tree);
}
