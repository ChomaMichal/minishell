/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 15:33:23 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/30 14:49:41 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(int n)
{
	size_t	len;
	long	num;

	len = 1;
	num = (long)n;
	if (num < 0)
	{
		num = -num;
		len++;
	}
	while (num / 10)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	len;
	char	*res;
	long	num;

	num = (long)n;
	len = num_len(n);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = 0;
	if (n < 0)
	{
		res[0] = '-';
		num = -num;
	}
	while (num && len--)
	{
		res[len] = (num % 10) + '0';
		num /= 10;
	}
	if (n == 0)
		res[0] = '0';
	return (res);
}

// #include <stdio.h>
// int main(void)
// {
// 	printf("%s\n", ft_itoa(2));
// 	return (0);
// }