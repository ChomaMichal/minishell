/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:50:59 by josefelghna       #+#    #+#             */
/*   Updated: 2025/08/29 21:21:50 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(t_token *token)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->token = token;
	node->next = NULL;
	return (node);
}

// #include <stdio.h>
// #include <unistd.h>

// int main(void)
// {
// 	t_list	*x;
// 	int	num = 65;

// 	x = ft_lstnew(&num);
// 	printf("%s\n", (char *)(*x).content);
// 	x = ft_lstnew("hahaha hohoho");
// 	printf("%s\n", (char *)(*x).content);
// 	// write (1, x, sizeof(int));
// 	return (0);
// }
