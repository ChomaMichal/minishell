/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:15:32 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/13 15:29:11 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	execute(t_btree *tree, t_data *data)
{
	if (tree == NULL)
		return ;
	else if (tree->type == BNODE_SUBSHELL)
		ft_subshell(tree, data);
	else if (tree->type == BNODE_AND)
		ft_and(tree, data);
	else if (tree->type == BNODE_OR)
		ft_or(tree, data);
	else if (tree->type == BNODE_COMMAND)
		ft_command(tree, data);
	else if (tree->type == BNODE_PIPE)
		ft_pipe(tree, data);
}
