/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:33:57 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/10 15:34:34 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "../minishell.h"

int	ft_exit(t_data *data, char *str)
{
	int	i;

	if (data->head != NULL)
		btree_apply_suffix(data->head, delete_bnode);
	free_arr((void ***)&data->env);
	i  = ft_atoi(str);
	free(str);
	exit(i);
}
