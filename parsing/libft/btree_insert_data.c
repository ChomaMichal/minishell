/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:50:32 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/08/08 21:06:05 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	btree_insert_data(t_btree **root, t_bitem *item, int (*cmpf)(void *, void *))
{
	t_btree	*new_node;
	t_btree	*cur_node;

	cur_node = *root;
	if (!*root)
	{
		new_node = btree_create_node(item);	
		if (!new_node)
			return ;
		*root = new_node;
		return ;
	}
	if (cmpf(cur_node->item, item) > 0)
		btree_insert_data(&cur_node->left, item, cmpf);
	else
		btree_insert_data(&cur_node->right, item, cmpf);
}
