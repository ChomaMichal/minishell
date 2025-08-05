/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:34:05 by josefelghna       #+#    #+#             */
/*   Updated: 2025/04/23 18:14:15 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = -1;
	while (*s)
		f((unsigned int)++i, s++);
}

// void	to_upper(unsigned int i, char *c)
// {
// 	if (i < 3)
// 		if (97 <= *c && *c <= 122)
// 			*c = *c - 32;
// }

// #include <stdio.h>
// int main(void)
// {
// 	char	str[] = "this will be capital";
// 	ft_striteri(str, &to_upper);
// 	printf("%s\n", str);
// 	return (0);
// }