/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:09:04 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/06 14:19:39 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_btree	*parse_and_or(t_list **tokens, t_here_doc **here_list, int *flag);

t_btree	*parse_command_args(t_list **tokens, t_here_doc **here_list, int *flag)
{
	t_list	*cur;
	t_btree	*bnode;

	cur = *tokens;
	bnode = make_bnode(BNODE_COMMAND, NULL, NULL, flag);
	if (*flag)
		return (palloc_err(), bnode);
	bnode->cmd_argv = create_cmd_argv(tokens, flag);
	if (!bnode->cmd_argv)
		return (palloc_err(), delete_bnode(bnode), NULL);
	if (bnode->cmd_argv[0] == NULL)
		bnode->empty_cmd = 1;
	if (create_redirections(tokens, bnode, here_list))
	{
		*flag = 1;
		return (palloc_err(), bnode);
	}
	while (cur && (cur->token->options & WORD
			|| cur->token->options & REDIR_OP))
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
		if (*flag)
			return (bnode);
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
	if (*flag)
		return (left);
	while (*tokens && (*tokens)->token->options & PIPE)
	{
		consume_token(tokens);
		right = parse_command(tokens, here_list, flag);
		if (*flag)
			return (left);
		left = make_bnode(BNODE_PIPE, left, right, flag);
		if (*flag)
			return (left);
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
	if (*flag)
		return (left);
	while ((*tokens)
		&& ((*tokens)->token->options & AND || (*tokens)->token->options & OR))
	{
		cur = *tokens;
		consume_token(tokens);
		right = parse_pipeline(tokens, here_list, flag);
		if (*flag)
			return (left);
		if (cur->token->options & AND)
			left = make_bnode(BNODE_AND, left, right, flag);
		else if (cur->token->options & OR)
			left = make_bnode(BNODE_OR, left, right, flag);
		if (*flag)
			return (delete_bnode(right), left);
	}
	return (left);
}

t_btree	*create_exec_tree(t_parse_data *d)
{
	t_btree	*tree;
	int		flag;
	t_list	*tokens;

	flag = 0;
	tokens = d->tokens;
	tree = parse_and_or(&tokens, &d->here_list, &flag);
	if (flag)
		return (btree_apply_suffix(tree, delete_bnode), NULL);
	if (open_write_here_docs(&d->here_list, d))
		return (printf("run_here_doc() failed\n"),
			btree_apply_suffix(tree, delete_bnode), NULL);
	return (tree);
}
