/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:07:15 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/09/04 15:53:00 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_c(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}

int	write_s(int fd, char *str)
{
	int	len;

	if (!str)
		return (write(fd, "(null)", 6), 6);
	len = ft_strlen(str);
	write(fd, str, len);
	return (len);
}

int	write_p(int fd, void *ptr)
{
	if (!ptr)
		return (write(1, "(nil)", 5), 5);
	write(fd, "0x", 2);
	return (ft_putnbr_base_p(fd, (uintptr_t)ptr, "0123456789abcdef") + 2);
}

int	write_di(int fd, int num)
{
	return (ft_putnbr_base(fd, (long)num, "0123456789"));
}
