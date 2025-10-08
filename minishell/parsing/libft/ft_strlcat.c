/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:55:08 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/22 14:31:02 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	i_dst;
	size_t	i_src;
	size_t	len;

	i_dst = 0;
	i_src = 0;
	len = ft_strlen(src);
	while (dst[i_dst] && i_dst < dsize)
		i_dst++;
	if (i_dst == dsize)
		return (len + dsize);
	len += i_dst;
	while (src[i_src] && i_dst + 1 < dsize)
		dst[i_dst++] = src[i_src++];
	dst[i_dst] = 0;
	return (len);
}

// #include <stdio.h>
// #include <string.h>
// int main() {
//     char buffer[12] = "Hello";  // Buffer size is 12, string length is 5
//     char *src = " World!"; // String to append

//     size_t result = ft_strlcat(buffer, src, sizeof(buffer));

//     printf("Buffer after strlcat: \"%s\"\n", buffer);
//     printf("Total length that would have been produced: %zu\n", result);

//     // Case where buffer is too small
//     char small_buffer[8] = "Hi";
//     result = ft_strlcat(small_buffer, " there!", sizeof(small_buffer));

//     printf("Small buffer after strlcat: \"%s\"\n", small_buffer);
//     printf("Required buffer size for full concat: %zu\n", result);

//     return 0;
// }