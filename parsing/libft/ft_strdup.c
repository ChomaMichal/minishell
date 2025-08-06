/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:13:08 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/28 13:05:22 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*p;

	len = ft_strlen(s) + 1;
	p = malloc(len * sizeof(char));
	if (!p)
		return (NULL);
	ft_strlcpy(p, s, len);
	return (p);
}

// #include <stdio.h>
// int main(void)
// {
// 	char	*p;

// 	p = ft_strdup("\n");
// 	printf("%s", p);
// 	free(p);
// 	return (0);
// }