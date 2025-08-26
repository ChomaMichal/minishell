/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:07:32 by josefelghna       #+#    #+#             */
/*   Updated: 2025/08/26 17:55:48 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->str);
		lst = lst->next;
	}
}

void	ft_lstnodeiter(t_list *lst, void(*f)(void *))
{
	while (lst)
	{
		f(lst);
		lst = lst->next;
	}
}
