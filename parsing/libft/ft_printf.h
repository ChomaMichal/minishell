/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:07:20 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/05/12 13:07:04 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

void	handle_sign(char c, va_list args, int *count);
int		parse_format(const char *format, va_list args, int *count);
int		ft_printf(const char *format, ...);
int		is_valid_sign(char c);
int		ft_putnbr_base(long nbr, char *base);
int		ft_putnbr_base_p(uintptr_t nbr, char *base);
int		write_c(char c);
int		write_s(char *str);
int		write_p(void *ptr);
int		write_di(int num);
int		write_u(unsigned int num);
int		write_x(unsigned int num);
int		write_cap_x(unsigned int num);

#endif
