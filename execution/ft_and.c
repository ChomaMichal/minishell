/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:00:51 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/17 15:04:52 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/libft/libft.h"
#include "executor.h"

void	ft_and(t_btree *tree, t_data *data)
{
	int		rt;

	execute(tree->left, data);
	rt = wait_and_get_exit_value(data->pids);
	free_pids(&data->pids);
	if (rt == 0)
		execute(tree->right, data);
}
