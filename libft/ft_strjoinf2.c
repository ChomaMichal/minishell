/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 11:58:29 by mchoma            #+#    #+#             */
/*   Updated: 2025/11/04 11:58:51 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoinf2(const char *fr, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(fr, str);
	free(str);
	return (tmp);
}
