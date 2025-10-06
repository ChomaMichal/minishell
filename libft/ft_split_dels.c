/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_multiple_delimiters.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:53:07 by josefelghna       #+#    #+#             */
/*   Updated: 2025/10/06 19:40:21 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clear_arr(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}

static size_t	len_till_delimiter(char const *s, char *delimiter)
{
	size_t	i;

	i = 0;
	while (*s && !ft_strchr(delimiter, *s))
	{
		s++;
		i++;
	}
	return (i);
}

static int	one_more_string(char ***res, size_t arr_size,
	char const *s, char *delimiter)
{
	char	**tmp_arr;
	char	*sub_string;
	size_t	sub_size;
	size_t	i;

	i = -1;
	tmp_arr = malloc((arr_size + 1) * sizeof(char *));
	if (!tmp_arr)
		return (clear_arr(*res, arr_size), 0);
	while (++i < arr_size)
		tmp_arr[i] = (*res)[i];
	free(*res);
	*res = tmp_arr;
	if (*s == 0)
		return (1);
	sub_size = len_till_delimiter(s, delimiter);
	sub_string = malloc((sub_size + 1) * sizeof(char));
	if (!sub_string)
		return (clear_arr(*res, i), 0);
	ft_strlcpy(sub_string, s, sub_size + 1);
	(*res)[i] = sub_string;
	return (1);
}

char	**ft_split_del(char const *s, char *delimiter)
{
	char	**res;
	size_t	arr_size;

	arr_size = 0;
	res = NULL;
	while (*s)
	{
		if (!ft_strchr(delimiter, *s))
		{
			if (!one_more_string(&res, arr_size, s, delimiter))
				return (NULL);
			while (*s && !ft_strchr(delimiter, *s))
				s++;
			arr_size++;
		}
		while (*s && ft_strchr(delimiter, *s))
			s++;
	}
	if (!one_more_string(&res, arr_size, s, delimiter))
		return (NULL);
	res[arr_size] = NULL;
	return (res);
}

// #include <stdio.h>
// int main(void)
// {
// 	char **res = ft_split("", 'x');
// 	if (!res)
// 		printf("allocation failed, NOOB :D\n(NULL RETURNED)\n");
// 	else
// 	{
// 		for (int i = 0; res[i]; i++)
// 		{
// 			printf(">>%s<<\n", res[i]);
// 			free(res[i]);
// 		}
// 	}
// 	free(res);
// 	return (0);
// }