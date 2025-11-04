/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:17:42 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/08 18:55:29 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/libft.h"

int	star_match(char *match, char *str);

int	star_match(char *match, char *str);

int	star_match_recur(char *match, char *str);

static DIR	*ft_opendir(char *path, DIR **directory)
{
	*directory = opendir(path);
	return (*directory);
}

//need to remove . and .. files in current directory
char	**expand_star_append(char *match, char ***arr)
{
	DIR				*directory;
	struct dirent	*idk;
	char			path[PATH_MAX];
	char			*str;

	if (getcwd(path, PATH_MAX) == NULL)
		return (NULL);
	if (ft_opendir(path, &directory) == NULL)
		return (*arr);
	idk = readdir(directory);
	idk = readdir(directory);
	idk = readdir(directory);
	while (idk)
	{
		if (star_match_recur(match, idk->d_name) == 1)
		{
			str = ft_strdup(idk->d_name);
			if (str == NULL)
				return (closedir(directory), NULL);
			if (ft_append_arr_str(arr, str) == NULL)
				return (free(str), closedir(directory), NULL);
		}
		idk = readdir(directory);
	}
	return (free(idk), closedir(directory), *arr);
}

int main(int argc, char **argv)
{
	char	**paths;
	size_t	i;

	i = 0;
	paths = NULL;
	if (expand_star_append(argv[1], &paths) == NULL)
		return (free_arr((void***) &paths), 0);
	while (paths && paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}
	free_arr((void ***) &paths);
	return (0);
}
/*
int	star_match(char *match, char *str)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	int		star;
	size_t	change;

	star = 0;
	j = 0;
	i = 0;
	change = 0;
	while(1)
	{
		change = 0;
		if (match[j] == '*')
		{
			star = 1;
			j ++;
			change = 1;
		}
		while (star == 0 && str[i] == match[j] && str[i] && match[j])
		{
			i ++;
			j++;
			change = 1;
		}
		tmp = 0;
		while (star == 1 && str[i + tmp] == match[j + tmp] && str[i + tmp]
			&& match[j + tmp] && !(match[0] == '*' && i == 0))
			tmp ++;
		if ((match[j + tmp] == '*' || match[j + tmp] == 0) && tmp != 0)
		{
			j = j + tmp;
			i = i + tmp;
			star = 0;
			change = 1;
		}
		else if (star == 1)
			(i ++, change = 1);
		if (str[i] == 0 && match[j] == 0)
			return (1);
		if (str[i] != 0 && match[j] == '*' && match[j+1] == 0)
			return (1);
		if (match[j] == 0)
			return (0);
		if (str[i] == 0)
			return (0);
		if (change == 0)
			return (0);
	}
}*/
