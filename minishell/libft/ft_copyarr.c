/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyarr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:30:41 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/10/08 10:30:41 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_coppyarrstr(char **arr)
{
	size_t	i;
	char	**new;

	i = 0;
	while (arr[i])
		i ++;
	new = ft_calloc(i + 1, sizeof(char *));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		if (new[i] == NULL)
			return (free_arr((void ***)&new), NULL);
		i++;
	}
	new[i] = NULL;
	return (new);
}
