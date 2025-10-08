/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_level_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:25:20 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/08/07 01:31:33 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	btree_level_count(t_btree *root)
{
	if (!root)
		return (0);
	else if (!root->right && !root->left)
		return (0);
	else if (root->right || root->left)
		return (1);
	return (1 + (btree_level_count(root->right)
		|| btree_level_count(root->left)));
}
