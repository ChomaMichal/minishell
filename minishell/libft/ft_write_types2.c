/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_types2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:07:16 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/09/04 16:25:05 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_u(int fd, unsigned int num)
{
	return (ft_putnbr_base(fd, (long)num, "0123456789"));
}

int	write_x(int fd, unsigned int num)
{
	return (ft_putnbr_base(fd, (long)num, "0123456789abcdef"));
}

int	write_cap_x(int fd, unsigned int num)
{
	return (ft_putnbr_base(fd, (long)num, "0123456789ABCDEF"));
}
