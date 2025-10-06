/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_last_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:22:12 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/06 18:41:42 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "idlist.h"

int	add_last_id(t_ids *list, int id)
{
	if (list->next == NULL)
	{
		list->next = malloc(sizeof(t_ids));
		if (list->next == NULL)
			return (-1);
		list->next->next = NULL;
		list->next->pid = id;
		return (0);
	}
	return (add_last_id(list->next, id));
}
