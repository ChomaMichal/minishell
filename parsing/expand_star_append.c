/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star_append.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:07:30 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/03 19:07:31 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	star_forward(size_t *i, size_t *j, char *match, char *str)
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
		&& match[(*j) + 1 + tmp] && !(match[0] == '*' && i == 0))
		tmp ++;
	if ((match[(*j) + 1 + tmp] == '*'
			|| match[(*j) + 1 + tmp] == 0) && tmp != 0)
	{
		(*j) = (*j) + tmp + 1;
		(*i) = (*i) + tmp;
	}
	else
		(*i)++;
}

static int	star_match(char *match, char *str, int *stars_arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (1)
	{
		if (match[j] == '*' && str[i])
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
			if (str[i] != 0 && match[j] == '*' && match[j + 1] == 0)
				return (1);
			return (0);
		}
	}
}

// static void	star_forward(size_t *i, char *match, char *str, int *stars_arr)
// {
// 	size_t	tmp;

// 	tmp = 0;
// 	if (str[i[0]] != 0 && match[i[1]] == '*' && !stars_arr[i[1]]
// 		&& match[i[1] + 1] == 0)
// 	{
// 		while (str[i[0]])
// 			i[0] += 1;
// 		while (match[i[1]])
// 			i[1] += 1;
// 		return ;
// 	}
// 	while (str[i[0] + tmp] == match[i[1] + 1 + tmp] && str[i[0] + tmp]
// 		&& match[i[1] + 1 + tmp] && !(match[0] == '*' && !stars_arr[0]
// 			&& i == 0))
// 		tmp ++;
// 	if (((match[i[1] + 1 + tmp] == '*' && !stars_arr[i[1] + 1 + tmp])
// 			|| match[i[1] + 1 + tmp] == 0) && tmp != 0)
// 	{
// 		i[1] = i[1] + tmp + 1;
// 		i[0] = i[0] + tmp;
// 	}
// 	else
// 		i[0] += 1;
// }

// static int	star_match(char *match, char *str, int *stars_arr)
// {
// 	size_t	i[2];

// 	i[0] = 0;
// 	i[1] = 0;
// 	while (1)
// 	{
// 		if (match[i[1]] == '*' && str[i[0]] && !stars_arr[i[1]])
// 			star_forward(i, match, str, stars_arr);
// 		else if (match[i[1]] == str[i[0]] && match[i[1]] && str[i[0]])
// 		{
// 			i[0] += 1;
// 			i[1] += 1;
// 		}
// 		else
// 		{
// 			if (str[i[0]] == 0 && match[i[1]] == 0)
// 				return (1);
// 			if (str[i[0]] != 0 && match[i[1]] == '*' && !stars_arr[i[1]]
// 				&& match[i[1] + 1] == 0)
// 				return (1);
// 			return (0);
// 		}
// 	}
// }

char	**expand_star_append(char *match, char ***arr, int *stars_arr)
{
	DIR				*directory;
	struct dirent	*idk;
	char			path[PATH_MAX];
	char			*str;

	if (getcwd(path, PATH_MAX) == NULL) // CHECK HOW THIS FUNCTION BEHAVES ON ERRORS. (malloc?) need free?
		return (NULL);
	if (ft_opendir(path, &directory) == NULL)
		return (*arr);
	idk = readdir(directory);
	while (idk)
	{
		if (star_match(match, idk->d_name, stars_arr) == 1)
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
