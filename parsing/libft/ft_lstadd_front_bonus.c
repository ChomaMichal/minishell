/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:52:04 by josefelghna       #+#    #+#             */
/*   Updated: 2025/05/01 13:13:13 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>
// void	del(void *content)
// {
// 	free(content);
// }

// void	*to_upper(void *content)
// {
// 	char	*res;
// 	char	*str;
// 	size_t	i;

// 	i = 0;
// 	str = (char *)content;
// 	res = ft_strdup(str);
// 	if (!res)
// 		return (NULL);
// 	while (res[i])
// 	{
// 		res[i] = ft_toupper(res[i]);
// 		i++;
// 	}
// 	return (res);
// }

// int		main(void)
// {
// 	t_list	*lst;
// 	t_list	*tmp;

// 	// Always initialize :D
// 	lst = NULL;

// 	char	*s1 = ft_strdup("the content :O");
// 	t_list	*n1 = ft_lstnew(s1);
// 	if (!n1)
// 	{
// 		free(s1);
// 		s1 = "failed D:";
// 	}
// 	char	*s2 = ft_strdup("Bombini Guzini");
// 	t_list	*n2 = ft_lstnew(s2);
// 	if (!n2)
// 	{
// 		free(s2);
// 		s2 = "this too failed D:";
// 	}
// 	ft_lstadd_back(&lst, n1);
// 	ft_lstadd_back(&lst, n2);
// 	// ft_lstadd_back(&lst, ft_lstnew(ft_strdup("i'm the captain now")));
// 	// ft_lstadd_back(&lst, ft_lstnew(ft_strdup("this is the last")));
// 	tmp = lst;
// 	while (tmp)
// 	{
// 		if ((char *)tmp->content)
// 			printf("%s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	printf("\n");
// 	// printf("%d\n", ft_lstsize(lst));
// 	// if (lst)
// 	// 	printf("%s\n", (char *)ft_lstlast(lst)->content);
// 	// else
// 	// 	printf("list is empty, idiot :D\n");
// 	//////////////////////////////////////////
// 	// ft_lstclear(&lst, &del);
// 	// printf("\n");
// 	// if (lst)
// 	// 	printf("list not empty, smth wrong, should be cleared\n");
// 	// else
// 	// 	printf("list is empty, idiot :D (cleared)\n");
// 	/////////////////////////////////////////
// 	t_list *new_list = ft_lstmap(lst, &to_upper, &del);
// 	t_list *new_list_head = new_list;
// 	while (new_list)
// 	{
// 		printf("%s\n", (char *)new_list->content);
// 		new_list = new_list->next;
// 	}
// 	ft_lstclear(&new_list_head, &del);
// 	ft_lstclear(&lst, &del);
// 	return (0);
// }