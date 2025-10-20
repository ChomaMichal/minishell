/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:47:45 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/10 19:00:53 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

int	ft_echo(t_data *data, char *str, int flag)
{
	if (str != NULL && flag == 0)
	{
		if (printf("%s\n", str) == -1)
			return (set_rt(&data->rt, 1), 1);
	}
	else if (str != NULL && flag == 1)
	{
		if (printf("%s\n", str) == -1)
			return (set_rt(&data->rt, 1), 1);
	}
	else if (flag == 0)
	{
		if (printf("\n") == -1)
			return (set_rt(&data->rt, 1), 1);
	}
	return (set_rt(&data->rt, 0), 0);
}
