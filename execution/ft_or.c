/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:03:02 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/17 15:15:34 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../libft/idlist.h"

void	ft_or(t_btree *tree, t_data *data)
{
	int		rt;
	int		subshell;

	subshell = 0;
	if (data->subshell == 1)
	{
		data->subshell = 0;
		subshell = 1;
	}
	execute(tree->left, data);
	rt = wait_and_get_exit_value(data->pids);
	free_pids(&data->pids);
	if (subshell == 1)
		data->subshell = 1;
	if (rt != 0)
		execute(tree->right, data);
}
