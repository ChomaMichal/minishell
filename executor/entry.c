/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:15:32 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/06 17:24:39 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/libft/libft.h"
#include "executor.h"

void	command(t_btree *tree)
{
	get_path(,);
}


void	execute(t_btree *tree, t_data *envp)
{
	if (tree->type == BNODE_SUBSHELL)
		subshell(tree);
	else if (tree->type == BNODE_AND)
		and(tree);
	else if (tree->type == BNODE_OR)
		or(tree);
	else if (tree->type == BNODE_COMMAND)
		command(tree);
	else if (tree->type == BNODE_PIPE)
		pipe(tree);
}
