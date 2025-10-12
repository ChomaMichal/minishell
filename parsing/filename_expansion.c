/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 16:26:33 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/10/09 16:26:48 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	star_forward(size_t *i, size_t *j, char *match, char *str)
{
	size_t	tmp;

	tmp = 0;
	if (str[(*i)] != 0 && match[(*j)] == '*' && match[((*j)) + 1] == 0)
	{
		while (str[(*i)])
			(*i)++;
		while (match[(*j)])
			(*j)++;
		return ;
	}
	while (str[(*i) + tmp] == match[(*j) + 1 + tmp] && str[(*i) + tmp]
		&& match[(*j) + 1 + tmp])
		tmp ++;
	if ((match[(*j) + 1 + tmp] == '*' || match[(*j) + 1 + tmp] == 0) && tmp != 0)
	{
		(*j) = (*j) + tmp + 1;
		(*i) = (*i) + tmp;
	}
	else
		((*i)) ++;
}

int		star_match(char *match, char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while(1)
	{
		if (match[j] == '*' && match[j + 1] == '*')
			j ++;
		if (match[j] == '*' &&  str[i])
			star_forward(&i, &j, match, str);
		else if (match[j] == str[i] && match[j] && str[i])
		{
			i ++;
			j ++;
		}
		else
		{
			if (str[i] == 0 && match[j] == 0)
				return (1);
			if (match[j] == '*' && match[j + 1] == 0)
				return (1);
			return (0);
		}
	}
}

char	**expand_star_append(char *match, char ***arr)
{
	DIR				*directory;
	struct dirent	*idk;
	int				i;
	char			path[PATH_MAX];
	char			*str;

	if (getcwd(path, PATH_MAX) == NULL)
		return (NULL);
	i = 0;
	if (ft_opendir(path, &directory) == NULL)
		return (*arr);
	idk = readdir(directory);
	while (idk)
	{
		if (star_match(match, idk->d_name) == 1)
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
