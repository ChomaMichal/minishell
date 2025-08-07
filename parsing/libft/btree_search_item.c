/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 23:47:30 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/08/07 01:23:56 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*btree_search_item(t_btree *root, void *item, int (*cmpf)(void *, void *))
{
	if (cmpf(root->item, item) < 0)
		return (btree_search_item(root->left, item, cmpf));
	else if (cmpf(root->item, item) == 0)
		return (root->item);
	else
		return (btree_search_item(root->right, item, cmpf));
}
