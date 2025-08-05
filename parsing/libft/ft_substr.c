/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:22:05 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/28 13:05:37 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!len || s_len <= start)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, len + 1);
	return (res);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char	*sub;

// 	sub = ft_substr("0123456789", 0, 12);
// 	printf("%s\n", sub);
// 	free(sub);
// 	return (0);
// }