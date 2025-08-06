/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <mchoma@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 13:07:28 by mchoma            #+#    #+#             */
/*   Updated: 2025/08/06 13:35:08 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int	cd_path(t_data *data, char **path)
{
	char	*str;
	char	**arr;
	size_t	i;

	i  = 0;
	str = ft_get_env_value(data->env, "CDPATH");
	if (str == NULL)
		return (0);
	arr = ft_split(str, ':');
	if (arr == NULL)
		return (free(str), 0);
	free(str);
	while (arr[i])
	{
		str = ft_strjoin(arr[i], "/");
		if (str == NULL)
			return (free_arr((void ***)&arr), 0);
		str = ft_strjoinf1(str, *path);
		if (str == NULL)
			return (free_arr((void ***)&arr), 0);
		if (chdir (str) != -1)
			return (free_arr((void ***) &arr), free(str), 2);
		free(str);
		i++;
	}
	return (free_arr((void ***) &arr), 1);
}

int	ft_cd(t_data *data, char *path)
{
	char	*str;
	size_t	i;

	if (*path != '/')
	{
		i = cd_path(data, &path);
		if (i == 0)
			return (free(path), 0);
		if (i == 2)
			return (free(path), 2);
	}
	if (*path == 0)
	{
		free(path);
		path = ft_get_env_value(data->env, "HOME");
		if (path == NULL)
			return (0);
	}
	if (chdir(path) == -1)
	{
		data->rt = 1;
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (free(path), 0);
	}
	data->rt = 0;
	return (free(path), 1);
}
