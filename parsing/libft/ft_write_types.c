/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:07:15 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/05/09 18:46:12 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_c(char c)
{
	write(1, &c, 1);
	return (1);
}

int	write_s(char *str)
{
	int	len;

	if (!str)
		return (write(1, "(null)", 6), 6);
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}

int	write_p(void *ptr)
{
	if (!ptr)
		return (write(1, "(nil)", 5), 5);
	write(1, "0x", 2);
	return (ft_putnbr_base_p((uintptr_t)ptr, "0123456789abcdef") + 2);
}

int	write_di(int num)
{
	return (ft_putnbr_base((long)num, "0123456789"));
}
