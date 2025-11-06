/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:08:59 by mchoma            #+#    #+#             */
/*   Updated: 2025/11/06 14:22:35 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/idlist.h"

void	set_operators(char **operators)
{
	operators[0] = "||";
	operators[1] = "|";
	operators[2] = "&&";
	operators[3] = ">>";
	operators[4] = ">";
	operators[5] = "<<";
	operators[6] = "<";
	operators[7] = "(";
	operators[8] = ")";
	operators[9] = NULL;
}

void	delete_bnode(void *ptr)
{
	t_btree	*node;

	if (ptr)
	{
		node = (t_btree *)ptr;
		free_split(node->cmd_argv);
		free(node->ambig);
		clear_redir_list(&node->redir_list);
		free(node);
	}
}

void	delete_bnode_unlink(void *ptr)
{
	t_btree	*node;

	if (ptr)
	{
		node = (t_btree *)ptr;
		free_split(node->cmd_argv);
		free(node->ambig);
		clear_redir_list_unlink(&node->redir_list);
		free(node);
	}
}

void	cleanup(t_data *data)
{
	int		rt;

	rt = wait_and_get_exit_value(data->pids);
	if (rt != -1)
		data->rt = rt;
	free_pids(&data->pids);
	if (g_sgnl != 0)
	{
		data->rt = g_sgnl + 128;
		g_sgnl = 0;
	}
	if (data->subshell == 1)
		btree_apply_suffix(data->head, delete_bnode);
	if (data->subshell == 0)
		btree_apply_suffix(data->head, delete_bnode_unlink);
	data->head = NULL;
}
