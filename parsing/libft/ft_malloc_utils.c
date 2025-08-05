/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:20:48 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/06/30 22:20:57 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delete(void *ptr)
{
	free(ptr);
}

void	ft_add_address(void *ptr, int list_num)
{
	void	*node;
	t_list	**list;

	list = ft_alloc_list(list_num);
	node = ft_lstnew(ptr);
	if (!node)
	{
		ft_lstclear(list, &ft_delete);
		return_error(1);
	}
	ft_lstadd_back(list, node);
}

void	*ft_check_add(void *ptr, int ptrs_list, int error_num)
{
	if (!ptr)
		return_error(error_num);
	ft_add_address(ptr, ptrs_list);
	return (ptr);
}

void	*ft_check(void *ptr, int error_num)
{
	if (!ptr)
		return_error(error_num);
	return (ptr);
}
