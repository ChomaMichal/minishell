/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:53:53 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/25 17:34:38 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*p_src;
	unsigned char	*p_dest;

	p_src = (unsigned char *)src;
	p_dest = (unsigned char *)dest;
	if (!n)
		return (dest);
	if ((src <= dest && dest <= (src + n - 1))
		|| (dest <= src && src <= (dest + n - 1)))
		return (ft_memmove(dest, src, n));
	while (n--)
		*p_dest++ = *p_src++;
	return (dest);
}

// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*str = ft_strdup("123456789");
// 	// char	*dst = malloc(22 * sizeof(char));
// 	ft_memcpy(str + 5, str, 1000);
// 	printf("%s\n", str);
// 	// write(1, dst, 30);

// 	char	*str1 = ft_strdup("123456789");
// 	// char	*dst1 = malloc(22 * sizeof(char));
// 	memcpy(str1 + 5, str1, 1000);
// 	printf("%s\n", str1);
// 	return (0);
// }