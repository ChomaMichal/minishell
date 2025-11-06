/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:29:56 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/06 14:41:47 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	clear_redir_list(t_redir_list **redir_list)
{
	t_redir_list	*cur;
	t_redir_list	*next;

	cur = *redir_list;
	while (cur)
	{
		next = cur->next;
		free(cur->file_name);
		free(cur);
		cur = next;
	}
	*redir_list = NULL;
}

void	clear_redir_list_unlink(t_redir_list **redir_list)
{
	t_redir_list	*cur;
	t_redir_list	*next;

	cur = *redir_list;
	while (cur)
	{
		next = cur->next;
		if (cur->type == REDIR_HERE)
			unlink(cur->file_name);
		free(cur->file_name);
		free(cur);
		cur = next;
	}
	*redir_list = NULL;
}

void	clear_here_list(t_here_doc **here_list)
{
	t_here_doc	*cur;
	t_here_doc	*next;

	cur = *here_list;
	while (cur)
	{
		next = cur->next;
		free(cur->delimiter);
		free(cur->file_name);
		free(cur);
		cur = next;
	}
	*here_list = NULL;
}

void	clear_all_redirs(t_btree *bnode, t_here_doc **here_list)
{
	clear_redir_list(&bnode->redir_list);
	clear_here_list(here_list);
}
