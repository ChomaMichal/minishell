/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subshell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:54:05 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/10 15:25:18 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
void	ft_subshell(t_btree *tree, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid)
	{
		data->subshell = 1;
		execute(tree->left, data);
	}
	else
		add_last_id(&data->pids, pid);
}
