/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 15:07:32 by josefelghna       #+#    #+#             */
/*   Updated: 2025/09/09 19:20:04 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_print_d *), t_print_d *data)
{
	while (lst)
	{
		data->token = lst->token;
		f(data);
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
