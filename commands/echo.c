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
	if (flag == 0 && printf("%s\n", str) == -1)
	{
		data->rt = 1;
		return (free(str), set_rt(&data->rt, 1), 0);
	}
	if (flag == 1 && printf("%s", str) == -1)
	{
		data->rt = 1;
		return (free(str), set_rt(&data->rt, 1), 0);
	}
	data->rt = 0;
	return (free(str), set_rt(&data->rt, 0), 1);
}
