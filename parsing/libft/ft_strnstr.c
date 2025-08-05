/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:43:19 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/25 17:11:21 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lil_len;

	i = 0;
	lil_len = ft_strlen(little);
	if (lil_len == 0)
		return ((char *)big);
	if (len == 0 || lil_len > len)
		return (NULL);
	while (big[i] && i + lil_len <= len)
	{
		if (ft_strncmp(big + i, little, lil_len) == 0)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <unistd.h>

// int	main(void)
// {
// 	char *str = "VeryBigString1";
// 	// write(1, ft_strnstr("VeryBigString", "Big", 7), 40);
// 	// printf("%s\n", strnstr(str, "1", 14));
// 	printf("%s\n", ft_strnstr(str, "Ve", 1));
// 	printf("%s\n", &str[5]);
// 	return (0);
// }