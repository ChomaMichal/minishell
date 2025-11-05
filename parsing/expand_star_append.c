/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:07:30 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/05 12:21:52 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	star_match_recur(char *match, char *str, int *stars_arr);

void	star_forward(size_t *i, size_t *j, char *match, char *str, int *stars_arr)
{
	size_t	tmp;

	tmp = 0;
	if (str[(*i)] != 0 && match[(*j)] == '*' && !stars_arr[(*j)] && match[((*j)) + 1] == 0)
	{
		while (str[(*i)])
			(*i)++;
		while (match[(*j)])
			(*j)++;
		return ;
	}
	while (str[(*i) + tmp] == match[(*j) + 1 + tmp] && str[(*i) + tmp]
		&& match[(*j) + 1 + tmp] && !(match[0] == '*' && !stars_arr[0] && i == 0))
		tmp ++;
	if ((match[(*j) + 1 + tmp] == '*' && !stars_arr[(*j) + 1 + tmp]
			|| match[(*j) + 1 + tmp] == 0) && tmp != 0)
	{
		(*j) = (*j) + tmp + 1;
		(*i) = (*i) + tmp;
	}
}

int	star_forward_wrap(char *match, char *str, int *stars_arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (match[0] == '*' && stars_arr[0] == 0
		&& match[1] == '*' && stars_arr[1] == 0)
	{
		match++;
		stars_arr ++;
	}
	if (match[0] != '*' || stars_arr[0] || match[0] == 0 || str[0] == 0)
		return (0);
	if (match[0] == '*' && !stars_arr[0] && str[0])
		star_forward(&i, &j, match, str, stars_arr);
	if (i != 0 && star_match_recur(match + j, str + i, stars_arr + j) == 1)
		return (1);
	return (star_forward_wrap(match, str + 1, stars_arr));
}


int	star_match_recur(char *match, char *str, int *stars_arr)
{
	if ((str[0] != 0 && match[0]  == 0) || (str[0] == 0 && match[0]  != 0))
		return (0);
	if (str[0] == 0 && match[0] == 0)
		return (1);
	if (str[0] != 0 && match[0] == '*' && !stars_arr[0] && match[1] == 0)
		return (1);
	else if (match[0] == str[0] && match[0] && str[0])
		return (star_match_recur(match + 1, str + 1, stars_arr + 1));
	else if (match[0] == '*' && !stars_arr[0] && str[0])
		return (star_forward_wrap(match, str, stars_arr));
	return (0);
}

char	**expand_star_append(char *match, char ***arr, int *stars_arr)
{
	DIR				*directory;
	struct dirent	*idk;
	char			path[PATH_MAX];
	char			*str;

	// printf("on (%s) stars_arr is:[", match);
	// for (size_t i = 0; i < ft_strlen(match); i++)
	// 	printf("%i", stars_arr[i]);
	// printf("]\n");
	if (getcwd(path, PATH_MAX) == NULL) // CHECK HOW THIS FUNCTION BEHAVES ON ERRORS. (malloc?) need free?
		return (NULL);
	if (ft_opendir(path, &directory) == NULL)
		return (*arr);
	idk = readdir(directory);
	while (idk)
	{
		if (star_match_recur(match, idk->d_name, stars_arr) == 1)
		{
			str = ft_strdup(idk->d_name);
			if (str == NULL)
				return (free_arr(arr), closedir(directory), NULL);
			if (ft_append_arr_str(arr, str) == NULL)
				return (free(str), free_arr(arr), closedir(directory), NULL);
		}
		idk = readdir(directory);
	}
	return (free(idk), closedir(directory), *arr);
}
