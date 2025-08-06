/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:54:02 by josefelghna       #+#    #+#             */
/*   Updated: 2025/06/28 15:53:52 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
		*p++ = (unsigned char)c;
	return (s);
}

// THIS FT_MEMSET IS VERY SLOW. CONSIDER CHANGING IT...
// MAKE IT WRITE 8 by 8 BYTES

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str;

// 	str = ft_strdup("hi, this is it !!!!");
// 	ft_memset(str, '2', 5);
// 	printf("%s", str);
// 	return (0);
// }