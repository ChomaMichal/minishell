/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:07:12 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/05/12 17:12:03 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	handle_sign(char c, va_list args, int *count)
{
	if (c == '%')
		*count += write(1, "%", 1);
	else if (c == 'c')
		*count += write_c(va_arg(args, int));
	else if (c == 's')
		*count += write_s(va_arg(args, char *));
	else if (c == 'p')
		*count += write_p(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		*count += write_di(va_arg(args, int));
	else if (c == 'u')
		*count += write_u(va_arg(args, unsigned int));
	else if (c == 'x')
		*count += write_x(va_arg(args, unsigned int));
	else if (c == 'X')
		*count += write_cap_x(va_arg(args, unsigned int));
}

int	parse_format(const char *format, va_list args, int *count)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	i = -1;
	while (format[++i])
	{
		ptr = ft_strchr(&format[i], '%');
		if (!ptr)
			return (*count += ft_putstr_fd((char *)&format[i], 1), 1);
		len = (size_t)(ptr - &format[i]);
		write(1, &format[i], len);
		i += len + 1;
		*count += len;
		if (!is_valid_sign(format[i]))
		{
			*count += 2 - (format[i] == 0);
			write(1, &format[i - 1], 2 - (format[i] == 0));
			if (format[i] == 0)
				break ;
		}
		else if (format[i])
			handle_sign(format[i], args, count);
	}
	return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	if (!format || write(1, NULL, 0) < 0)
		return (-1);
	if (!ft_strchr(format, '%'))
		return (write(1, format, ft_strlen(format)));
	if (ft_strlen(format) == 1 && format[0] == '%')
		return (-1);
	va_start(args, format);
	parse_format(format, args, &count);
	va_end(args);
	return (count);
}
