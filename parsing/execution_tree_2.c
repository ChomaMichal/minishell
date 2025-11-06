/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tree_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:12:56 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/06 14:15:32 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_list	*consume_token(t_list **tokens)
{
	t_list	*cur;

	cur = *tokens;
	if (cur)
		*tokens = cur->next;
	return (cur);
}

t_btree	*make_bnode(t_bnode_type type, t_btree *left, t_btree *right, int *flag)
{
	t_btree	*node;

	node = malloc(sizeof(t_btree));
	if (!node)
	{
		*flag = 1;
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
		return (palloc_err(), free_split(cmd_argv), 1);
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
	while (cur && (cur->token->options & WORD
			|| cur->token->options & REDIR_OP))
	{
		if (cur->token->options & EMPTY_WORD
			|| cur->token->options & REDIR_WORD)
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

char	**create_cmd_argv(t_list **tokens, int *flag)
{
	t_list	*cur;
	size_t	word_count;
	char	**cmd_argv;

	word_count = 0;
	cur = *tokens;
	while (cur && (cur->token->options & WORD
			|| cur->token->options & REDIR_OP))
	{
		if (cur->token->options & REDIR_OP || cur->token->options & REDIR_WORD
			|| cur->token->options & HERE_DEL_WORD)
			cur = cur->next;
		else if (!(cur->token->options & EMPTY_WORD))
			word_count++;
		if (cur)
			cur = cur->next;
	}
	cmd_argv = malloc(sizeof(char *) * (word_count + 1));
	if (!cmd_argv)
		return (*flag = 1, palloc_err(), NULL);
	if (store_words(tokens, cmd_argv))
		return (*flag = 1, NULL);
	return (cmd_argv);
}
