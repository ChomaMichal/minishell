#include "minishell.h"

/*
and_or:			pipeline { "&&" | "||" pipeline }
pipeline:		command { "|" command }
command:		simple_command | subshell
simple_command:	WORD { WORD }
subshell:		"(" and_or ")"
*/

t_btree	*parse_and_or(t_list **tokens);

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
	while (cur && cur->token->options & WORD)
	{
		if (cur->token->options & EMPTY_WORD)
		{
			cur = cur->next;
			consume_token(tokens);
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
	while (cur && cur->token->options & WORD)
	{
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

t_btree	*parse_command(t_list **tokens)
{
	t_list	*cur;
	t_btree	*node;

	cur = *tokens;
	if (!cur)
		return (NULL);
	if (cur->token->options & OPEN_PARENTHESIS)
	{
		consume_token(tokens);
		node = parse_and_or(tokens);
		cur = *tokens;
		if (!cur || !(cur->token->options & CLOSE_PARENTHESIS))
			return (ft_printf(2, "Error: Expected `)'\n"), NULL);
		consume_token(tokens);
		return (make_bnode(BNODE_SUBSHELL, node, NULL));
	}
	else if (cur->token->options & WORD)
	{
		node = make_bnode(BNODE_COMMAND, NULL, NULL);
		if (!node)
			return (ft_printf(2, "malloc failed in make_bnode(): parse_command()\n"), NULL);
		node->cmd_argv = create_cmd_argv(tokens);
		if (!node->cmd_argv)
			return (ft_printf(2, "malloc failed in create_cmd_argv\n"), NULL);
		return (node);
	}
	return (ft_printf(2, "Error: Unexpected token\n"), NULL);
}

t_btree	*parse_pipeline(t_list **tokens)
{
	t_btree	*left;
	t_btree	*right;
	t_list	*cur;

	left = parse_command(tokens);
	while (*tokens && (*tokens)->token->options & PIPE)
	{
		cur = *tokens;
		consume_token(tokens);
		right = parse_command(tokens);
		left = make_bnode(BNODE_PIPE, left, right);
	}
	return (left);
}

t_btree	*parse_and_or(t_list **tokens)
{
	t_btree	*left;
	t_btree	*right;
	t_list	*cur;

	left = parse_pipeline(tokens);
	while ((*tokens)
		&& ((*tokens)->token->options & AND || (*tokens)->token->options & OR))
	{
		cur = *tokens;
		consume_token(tokens);
		right = parse_pipeline(tokens);
		if (cur->token->options & AND)
			left = make_bnode(BNODE_AND, left, right);
		else if (cur->token->options & OR)
			left = make_bnode(BNODE_OR, left, right);
	}
	return (left);
}

t_btree	*create_tree(t_list *tokens)
{
	t_btree	*tree;

	tree = parse_and_or(&tokens);
	return (tree);
}
