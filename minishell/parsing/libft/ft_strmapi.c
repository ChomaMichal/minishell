/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:32:35 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/30 17:31:32 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*res;

	i = -1;
	len = ft_strlen(s);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (s[++i])
		res[i] = f(i, (s[i]));
	res[i] = 0;
	return (res);
}

// char	to_upper(unsigned int i, char c)
// {
// 	if (i < 15)
// 		if (97 <= c && c <= 122)
// 			return (c - 32);
// 	return (c);
// }

// #include <stdio.h>
// int main(void)
// {
// 	char	*str = ft_strmapi("", &to_upper);
// 	printf("%s\n", str);
// 	return (0);
// }
