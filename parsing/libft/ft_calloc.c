/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:35:50 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/28 13:05:24 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char		*ptr;

	if (nmemb * size == 0)
		return (malloc(0));
	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	return (ft_memset(ptr, 0, nmemb * size));
}

// #include <stdio.h>
// #include <unistd.h>
// int main(void)
// {
// 	char	*ptr = ft_calloc(0, 2);
// 	// free(ptr);
// 	printf("%d", ptr[0]);
// 	printf("%d", ptr[1]);
// 	printf("%d", ptr[2]);
// 	printf("%d", ptr[3]);
// 	printf("%d", ptr[4]);
// 	free(ptr);

// 	printf("\n");

// 	// char	*ptr2 = calloc(0, 2);
// 	// // free(ptr);
// 	// ptr2[0] = '0';
// 	// printf("%d", ptr2[0]);
// 	// printf("%d", ptr2[1]);
// 	// printf("%d", ptr2[2]);
// 	// printf("%d", ptr2[3]);
// 	// // printf("%d", ptr[4]);
// 	// free(ptr2);
// 	return (0);
// }