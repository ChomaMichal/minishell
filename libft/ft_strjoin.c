/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:50:27 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/08 10:36:03 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	counter;
	size_t	counter2;
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	counter = 0;
	counter2 = 0;
	while (s1 && s1[counter])
	{
		str[counter] = s1[counter];
		counter ++;
	}
	while (s2 && s2[counter2])
	{
		str[counter2 + counter] = s2[counter2];
		counter2 ++;
	}
	str[counter2 + counter] = 0;
	return (str);
}
