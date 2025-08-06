/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:37:40 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/06 16:38:07 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "../libft/libft.h"

int	ft_pwd(t_data *data)
{
	char	*path;

	path = malloc(PATH_MAX);
	if (path == NULL)
		return (ft_putstrerr("malloc error \n"), free(path), set_rt(&data->rt, 1), 0);
	if (getcwd(path, PATH_MAX) == NULL)
		return (ft_putstrerr("get_cwd error \n"), free(path), set_rt(&data->rt, 1), 0);
	if (printf("%s\n", path) == -1)
		return (ft_putstrerr("printf_eror\n"), free(path), set_rt(&data->rt, 1), 0);
	return (free(path), set_rt(&data->rt, 0), 1);
}
