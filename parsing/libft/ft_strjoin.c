/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:59:28 by josefelghna       #+#    #+#             */
/*   Updated: 2025/07/09 18:35:55 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res + ft_strlcpy(res, s1, len + 1), s2, len + 1);
	return (res);
}

char	*ft_strsjoin(char const *s1, char const *s2, char const *s3)
{
	char	*res;
	size_t	len;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	len = len1 + len2 + len3;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, len + 1);
	ft_strlcpy(res + len1, s2, len + 1);
	ft_strlcpy(res + len1 + len2, s3, len + 1);
	return (res);
}
// #include <stdio.h>
// int main(void)
// {
// 	printf("%s\n", ft_strjoin("", "23"));
// 	return (0);
// }