/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:20:17 by josefelghna       #+#    #+#             */
/*   Updated: 2025/05/08 13:01:32 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*node;
	t_list	*tmp;

	res = NULL;
	while (lst)
	{
		tmp = f(lst->content);
		if (!tmp)
			return (ft_lstclear(&res, del), NULL);
		node = ft_lstnew(tmp);
		if (!node)
			return (del(tmp), ft_lstclear(&res, del), NULL);
		ft_lstadd_back(&res, node);
		lst = lst->next;
	}
	return (res);
}
