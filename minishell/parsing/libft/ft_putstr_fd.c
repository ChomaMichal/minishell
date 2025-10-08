/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 23:56:06 by josefelghna       #+#    #+#             */
/*   Updated: 2025/07/03 16:01:42 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putstr_fd(char *s, int fd)
{
	int	len;

	len = 0;
	if (fd < 0)
		return (0);
	while (s[len])
		len++;
	write(fd, s, len);
	return (len);
}

// #include <fcntl.h>
// int main(void)
// {
// 	int fd;

// 	fd = open("test", O_RDWR);
// 	ft_putstr_fd("", fd);
// 	return (0);
// }