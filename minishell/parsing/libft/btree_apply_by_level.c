// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   btree_apply_by_level.c                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/08/07 01:32:33 by jel-ghna          #+#    #+#             */
// /*   Updated: 2025/08/08 15:38:43 by jel-ghna         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "libft.h"

// static int	*level(void)
// {
// 	static int	*ptr;

// 	if (!ptr)
// 	{
// 		ptr = malloc(sizeof(int *));
// 		if (!ptr)
// 			return (NULL);
// 		*ptr = 0;
// 	}
// 	return (ptr);
// }

// static int	*is_first(void)
// {
// 	static int	*ptr;

// 	if (!ptr)
// 	{
// 		ptr = malloc(sizeof(int *));
// 		if (!ptr)
// 			return (NULL);
// 		*ptr = 1;
// 	}
// 	return (ptr);
// }

// static void	free_globals(void)
// {
// 	free(level());
// 	free(is_first());
// }

// static int	init_globals(int *start, int **level_ptr, int **is_first_ptr)
// {
// 	*level_ptr = level();
// 	*is_first_ptr = is_first();
// 	if (!*level_ptr)
// 		return (1);
// 	if (!*is_first_ptr)
// 		return (free(*level_ptr), 1);
// 	*start = 1;
// 	return (0);
// }

// static int	ft_power(int num, int power)
// {
// 	if (num == 0)
// 		return (!power);
// 	if (power == 0)
// 		return (1);
// 	return (num * ft_power(num, power - 1));
// }

// void btree_apply_by_level(t_btree *root,
// 	void (*applyf)(void *item, int current_level, int is_first_elem))
// {
// 	static int	start;
// 	int			*level_ptr;
// 	int			*is_first_ptr;

// 	if (!root)
// 		return ;
// 	if (!start)
// 		if (init_globals(&start, &level_ptr, &is_first_ptr))
// 			return ;
// 	applyf(root->item, level(), is_first());
// 	if (root->left || root->right)
// 	{
// 		*level() += 1;
// 		btree_apply_by_level(root->left, applyf);
// 		btree_apply_by_level(root->right, applyf);
// 	}
// }
