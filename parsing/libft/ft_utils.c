/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josefelghnam <josefelghnam@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:07:18 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/29 21:52:28 by josefelghna      ###   ########.fr       */
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

void	print_number(uintptr_t nb, char *base, unsigned int b_len, int *count)
{
	if (nb >= b_len)
		print_number(nb / b_len, base, b_len, count);
	write(1, &base[nb % b_len], 1);
	*count += 1;
}

int	ft_putnbr_base_p(uintptr_t nbr, char *base)
{
	uintptr_t	nb;
	int			count;

	count = 0;
	nb = (uintptr_t)nbr;
	print_number(nb, base, ft_strlen(base), &count);
	return (count);
}

int	ft_putnbr_base(long nbr, char *base)
{
	long	nb;
	int		count;

	count = 0;
	if (nbr < 0)
	{
		write(1, "-", 1);
		nb = (unsigned long)(-(nbr + 1)) + 1;
		count += 1;
	}
	else
		nb = (unsigned long)nbr;
	print_number(nb, base, ft_strlen(base), &count);
	return (count);
}
