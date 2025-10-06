/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:54:04 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/24 19:44:38 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i < dsize - 1 && dsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dsize > 0)
		dst[i] = 0;
	return (ft_strlen(src));
}

// #include <stdio.h>

// int main(void)
// {
// 	char src[] = "Hello, World!";
// 	char dest1[50];
// 	unsigned int size = 0; // Test size
// 	unsigned int result;

// 	// Testing your ft_strlcpy
// 	result = ft_strlcpy(dest1, src, size);
// 	printf("Returned value: %u\n", result);  
// 	printf("Destination after ft_strlcpy: '%s'\n", dest1);  // Should be "Hello"

// 	return 0;
// }