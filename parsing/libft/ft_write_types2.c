/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_types2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:07:16 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/05/09 18:34:45 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_u(unsigned int num)
{
	return (ft_putnbr_base((long)num, "0123456789"));
}

int	write_x(unsigned int num)
{
	return (ft_putnbr_base((long)num, "0123456789abcdef"));
}

int	write_cap_x(unsigned int num)
{
	return (ft_putnbr_base((long)num, "0123456789ABCDEF"));
}
