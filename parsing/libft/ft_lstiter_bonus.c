/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:07:32 by josefelghna       #+#    #+#             */
/*   Updated: 2025/09/01 00:43:02 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *, char *), char *line)
{
	while (lst)
	{
		f(lst->token, line);
		lst = lst->next;
	}
}

// void	ft_lstnodeiter(t_list *lst, void(*f)(void *))
// {
// 	while (lst)
// 	{
// 		f(lst);
// 		lst = lst->next;
// 	}
// }
