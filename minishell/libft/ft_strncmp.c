/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:16:12 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/08 10:36:30 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			counter;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	counter = 0;
	while (counter != n)
	{
		if (!str1[counter] && !str2[counter])
			return (str1[counter] - str2 [counter]);
		if (str1[counter] != str2[counter])
			return (str1[counter] - str2 [counter]);
		counter ++;
	}
	return (0);
}
