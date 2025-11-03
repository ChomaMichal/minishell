/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fragment_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:06:53 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/03 19:01:51 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	copy_old_stars_arr(int *old_arr, int *new_arr, size_t old_len)
{
	size_t	i;

	i = 0;
	if (!old_arr || old_len == 0)
		return ;
	while (i < old_len)
	{
		new_arr[i] = old_arr[i];
		i++;
	}
}

int	dont_mark_stars(t_list *target_node, size_t old_len, char *tmp)
{
	int	*stars_arr;

	stars_arr = ft_calloc(sizeof(int) * ft_strlen(tmp), 1);
	if (!stars_arr)
		return (1);
	copy_old_stars_arr(target_node->token->stars_arr, stars_arr, old_len);
	free(target_node->token->stars_arr);
	target_node->token->stars_arr = stars_arr;
	return (0);
}

int	mark_stars(t_list *target_node, size_t old_len, char *tmp)
{
	int	*stars_arr;

	stars_arr = ft_calloc(sizeof(int) * ft_strlen(tmp), 1);
	if (!stars_arr)
		return (1);
	copy_old_stars_arr(target_node->token->stars_arr, stars_arr, old_len);
	while (tmp[old_len])
	{
		if (tmp[old_len] == '*')
			stars_arr[old_len] = 1;
		old_len++;
	}
	free(target_node->token->stars_arr);
	target_node->token->stars_arr = stars_arr;
	return (0);
}
