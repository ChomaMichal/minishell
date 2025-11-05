/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:33:57 by mchoma            #+#    #+#             */
/*   Updated: 2025/11/03 21:03:28 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "../minishell.h"
#include "../libft/idlist.h"

int	ft_exit(t_data *data, char *str)
{
	int	i;

	if (str)
		i = ft_atoi(str);
	else
		i = data->rt;
	if (data->head != NULL && data->subshell == 1)
		btree_apply_suffix(data->head, delete_bnode);
	else if (data->head != NULL && data->subshell == 0)
		btree_apply_suffix(data->head, delete_bnode_unlink);
	free_pids(&data->pids);
	free_arr((void ***)&data->env);
	exit(i);
}
