/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binsearch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:21:55 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/06 17:22:06 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	*isbin(char *path, char *command)
{
	char	*binpath;
	char	*tmp;

	if (command == NULL || path == NULL)
		return (NULL);
	tmp = ft_strjoin("/", command);
	if (!tmp)
		return (ft_putstr_fd("Malloc failed\n", 2), NULL);
	binpath = ft_strjoin(path, tmp);
	free(tmp);
	if (binpath)
	{
		if (access(binpath, X_OK) == 0)
			return (binpath);
	}
	free(binpath);
	return (NULL);
}

void	ft_free_split(char ***split)
{
	int		i;

	i = 0;
	while (split && (*split) && (*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
}

char	*get_path_path(char**envp, char *command)
{
	int		i;
	int		j;
	char	**arr;
	char	*path;

	arr = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			arr = ft_split(envp[i] + 5, ':');
			j = 0;
			while (arr && arr[j])
			{
				path = isbin(arr[j], command);
				if (path)
					return (ft_free_split(&arr), path);
				j++;
			}
		}
		i ++;
	}
	return (ft_putstr_fd("Didn't find executable binary\n", 2),
		ft_free_split(&arr), NULL);
}

char	*get_path(char**envp, char *command)
{
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) == 0)
		{
			if (access(command, X_OK) == 0)
				return (ft_strdup(command));
			ft_putstr_fd("Binary isn't executable\n", 2);
		}
		ft_putstr_fd("Didn't find executable binary\n", 2);
		return (NULL);
	}
	return (get_path_path(envp, command));
}
