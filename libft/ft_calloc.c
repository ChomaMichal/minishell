/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 12:11:54 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/08 10:30:22 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;
	size_t	i;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	i = (nmemb * size);
	if (i / nmemb != size)
		return (NULL);
	str = malloc (i);
	if (str == NULL)
		return (NULL);
	while (i--)
		str[i] = 0;
	return ((void *) str);
}
