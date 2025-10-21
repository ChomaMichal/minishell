/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:42:35 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/10/21 21:35:53 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	add_token(t_list **head, t_token *token)
{
	t_list	*node;

	node = ft_lstnew(token);
	if (!node)
		return (palloc_err(), 1);
	ft_lstadd_back(head, node);
	return (0);
}

t_token	*create_token(int is_redir_word)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->fragment_count = 0;
	token->fragments = NULL;
	token->options = 0;
	if (is_redir_word)
		token->options |= REDIR_WORD;
	token->str = NULL;
	token->fragment_i = 0;
	token->redir.append = 0;
	token->redir.in = NULL;
	token->redir.out = NULL;
	return (token);
}
