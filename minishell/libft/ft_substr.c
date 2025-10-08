/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:47:13 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/08 10:36:40 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	counter;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub = malloc(sizeof(char) * len + 1);
	if (sub == 0)
		return (0);
	counter = 0;
	while (counter < len && s[start + counter])
	{
		sub[counter] = s[start + counter];
		counter ++;
	}
	sub[counter] = 0;
	return (sub);
}
