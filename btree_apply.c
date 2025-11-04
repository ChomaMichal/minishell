/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:28:14 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/04 21:40:01 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	btree_apply_prefix(t_btree *root, void (*applyf)(void *))
{
	applyf(root);
	if (root && root->left)
		btree_apply_prefix(root->left, applyf);
	if (root && root->right)
		btree_apply_prefix(root->right, applyf);
}

void	btree_apply_infix(t_btree *root, void (*applyf)(void *))
{
	if (root && root->left)
		btree_apply_infix(root->left, applyf);
	applyf(root);
	if (root && root->right)
		btree_apply_infix(root->right, applyf);
}

void	btree_apply_suffix(t_btree *root, void (*applyf)(void *))
{
	if (root && root->left)
		btree_apply_suffix(root->left, applyf);
	if (root && root->right)
		btree_apply_suffix(root->right, applyf);
	applyf(root);
}
