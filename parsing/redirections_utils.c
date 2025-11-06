/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:29:54 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/06 14:41:53 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	add_redir_node(t_redir_list **redir_list, int options, char *file_name)
{
	t_redir_list	*new_node;
	t_redir_list	*cur;

	new_node = malloc(sizeof(t_redir_list));
	if (!new_node)
		return (1);
	new_node->type = get_redir_type(options);
	if (!(options & HERE_DOC))
	{
		new_node->file_name = ft_strdup(file_name);
		if (!new_node->file_name)
			return (free(new_node), 1);
	}
	else
		new_node->file_name = NULL;
	new_node->next = NULL;
	if (!*redir_list)
		*redir_list = new_node;
	else
		redir_list_last(*redir_list)->next = new_node;
	return (0);
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
	here_node->file_name = NULL;
	if (!here_node->delimiter)
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

t_redir_list	*redir_list_last(t_redir_list *node)
{
	t_redir_list	*cur;

	cur = node;
	while (cur->next)
		cur = cur->next;
	return (cur);
}
