/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:18:10 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/28 13:20:53 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const *set, char c)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	size_t	i;
	char	*res;

	len = ft_strlen(s1);
	start = 0;
	i = len - 1;
	while (i > 0 && in_set(set, s1[i]))
	{
		len--;
		i--;
	}
	while (s1[start] && start <= i && in_set(set, s1[start]))
	{
		start++;
		len--;
	}
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + start, len + 1);
	return (res);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%s\n", ft_strtrim("++!sssqweqwe....", "+!."));
// 	printf("%s\n", ft_strtrim("++!sssqweqwe", "+!."));
// 	printf("%s\n", ft_strtrim("sssqweqwe....", "+!."));
// 	printf("%s\n", ft_strtrim("sssqweqwe", "+!."));
// 	printf("%s\n", ft_strtrim("ss!.sq++we..qwe", "+!."));
// 	printf("%s\n", ft_strtrim("++!s.ss....!!++qwe!!.qw!e....", "+!."));
// 	printf("%s\n", ft_strtrim("", "+!."));
// 	printf("%s\n", ft_strtrim("++!sssqweqwe....", ""));
// 	printf("%s\n", ft_strtrim("", ""));
// 	printf("%s\n", ft_strtrim(" ", " "));
// 	return (0);
// }