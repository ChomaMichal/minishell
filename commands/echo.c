/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:47:45 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/06 17:05:14 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "../minishell.h"
#include "../libft/libft.h"


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
