/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:07:18 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/10/08 11:06:50 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_valid_sign(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

void	print_number(int fd, uintptr_t nb, t_base base, int *count)
{
	if (nb >= base.b_len)
		print_number(fd, nb / base.b_len, base, count);
	write(fd, &base.base[nb % base.b_len], 1);
	*count += 1;
}

int	ft_putnbr_base_p(int fd, uintptr_t nbr, char *base)
{
	uintptr_t	nb;
	int			count;
	t_base		base_d;

	base_d.base = base;
	base_d.b_len = ft_strlen(base);
	count = 0;
	nb = (uintptr_t)nbr;
	print_number(fd, nb, base_d, &count);
	return (count);
}

int	ft_putnbr_base(int fd, long nbr, char *base)
{
	long	nb;
	int		count;
	t_base	base_d;

	base_d.base = base;
	base_d.b_len = ft_strlen(base);
	count = 0;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nb = (unsigned long)(-(nbr + 1)) + 1;
		count += 1;
	}
	else
		nb = (unsigned long)nbr;
	print_number(fd, nb, base_d, &count);
	return (count);
}
