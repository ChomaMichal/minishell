/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josefelghnam <josefelghnam@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:17:04 by josefelghna       #+#    #+#             */
/*   Updated: 2025/06/29 15:57:58 by josefelghna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_digit_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			sign = -1;
	if (ft_digit_strlen(&nptr[i]) > 11)
		return (2147483647);
	while ('0' <= nptr[i] && nptr[i] <= '9')
		res = res * 10 + (nptr[i++] - '0');
	if (res > 2147483647 && sign == 1)
		return (2147483647);
	if (res > 2147483647 && sign == -1)
		return (-2147483648);
	return ((int)res * sign);
}

long	ft_atoi_but_better(const char *nptr)
{
	size_t	i;
	long	sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((9 <= nptr[i] && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
		if (nptr[i++] == '-')
			sign = -1;
	if (ft_digit_strlen(&nptr[i]) > 11)
		return (2147483648);
	while ('0' <= nptr[i] && nptr[i] <= '9')
		res = res * 10 + (nptr[i++] - '0');
	if (res > 2147483647 && sign == 1)
		return (2147483648);
	if (res > 2147483648 && sign == -1)
		return (2147483648);
	return (res * sign);
}

int	ft_hextoi_base(char *str, char *base)
{
	int		i;
	int		j;
	int		sign;
	int		res;

	sign = 1;
	i = -1;
	res = 0;
	if ((str[++i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = -sign;
	i += 2;
	while (str[i] && (ft_strchr(base, str[i])
			|| ft_strchr(base, ft_tolower(str[i]))))
	{
		j = 0;
		while (base[j] != str[i] && base[j] != ft_tolower(str[i]))
			j++;
		res = res * (int)ft_strlen(base) + j;
		i++;
	}
	return (res * sign);
}
