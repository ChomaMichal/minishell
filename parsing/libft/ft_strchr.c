/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:08:22 by josefelghna       #+#    #+#             */
/*   Updated: 2025/05/09 18:46:09 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s++)
		if (*(s - 1) == c)
			return ((char *)(s - 1));
	if (c == 0)
		return ((char *)(s - 1));
	return (NULL);
}

// #include <stdio.h>
// #include <unistd.h>

// int	main(void)
// {
// 	printf("%s\n", ft_strchr("this is the string", 0));
// 	// write(1, ft_strchr(str, 'i'), 1);
// 	return (0);
// }