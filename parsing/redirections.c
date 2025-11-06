/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:41:19 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/06 14:49:01 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2025/10/29 12:45:44 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_ambiguous_redir(t_list *tokens)
{
	t_list	*cur;
	size_t	expand_count;

	expand_count = 0;
	cur = tokens;
	if (cur->token->options & EMPTY_WORD)
		return (1);
	while (cur && cur->token->options & REDIR_WORD)
	{
		expand_count++;
		cur = cur->next;
	}
	if (expand_count > 1)
		return (1);
	return (0);
}

t_redir_type	get_redir_type(int options)
{
	if (options & OUTPUT_REDIR)
		return (REDIR_OUT);
	else if (options & OUTPUT_REDIR_APPEND)
		return (REDIR_OUT_APP);
	else if (options & INPUT_REDIR)
		return (REDIR_IN);
	else if (options & HERE_DOC)
		return (REDIR_HERE);
	return (0);
}

int	create_redirections(t_list **tokens, t_btree *bnode, t_here_doc **here_list)
{
	t_list	*cur;

	cur = *tokens;
	while (cur && (cur->token->options & WORD
			|| cur->token->options & REDIR_OP))
	{
		if (cur->token->options & REDIR_OP)
		{
			if (is_ambiguous_redir(cur->next))
			{
				bnode->ambig = ft_strdup(cur->token->redir_word);
				if (!bnode->ambig)
					return (clear_all_redirs(bnode, here_list), 1);
			}
			if (add_redir_node(&bnode->redir_list, cur->token->options,
					cur->next->token->str))
				return (clear_all_redirs(bnode, here_list), 1);
			if (cur->token->options & HERE_DOC)
				if (add_here_node(here_list, cur->next->token->str, bnode))
					return (clear_all_redirs(bnode, here_list), 1);
			cur = cur->next;
		}
		cur = cur->next;
	}
	return (0);
}
