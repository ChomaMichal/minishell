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

	execute(tree->left, data);
	rt = wait_and_get_exit_value(data->pids);
	free_pids(&data->pids);
	if (rt != 0)
		execute(tree->right, data);
}
