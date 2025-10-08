/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:47:07 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/05/03 20:12:59 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	has_nl(char *buffer, ssize_t bytes_read)
{
	ssize_t	i;

	i = 0;
	while (i < bytes_read)
		if (buffer[i++] == '\n')
			return (i - 1);
	return (-1);
}

void	lstclear(t_chunk **lst)
{
	t_chunk	*next;

	while (*lst)
	{
		next = (*lst)->next;
		free((*lst)->chunk);
		free((*lst));
		*lst = next;
	}
	*lst = NULL;
}

int	lstadd_back(t_chunk **lst, t_chunk *new)
{
	t_chunk	*node;

	if (!new)
		return (0);
	node = *lst;
	if (!node)
		return (*lst = new, 1);
	while (node->next)
		node = node->next;
	node->next = new;
	return (1);
}

t_chunk	*lst_new(char *str, ssize_t bytes_read)
{
	t_chunk	*node;

	node = malloc(sizeof(t_chunk));
	if (!node)
		return (NULL);
	node->chunk = malloc(bytes_read * sizeof(char));
	if (!(node->chunk))
		return (free(node), NULL);
	node->size = bytes_read;
	ft_memcpy(node->chunk, str, bytes_read);
	node->next = NULL;
	return (node);
}

void	*ft_memcpy(void *dest, const void *src, ssize_t n)
{
	unsigned char	*p_src;
	unsigned char	*p_dest;

	p_src = (unsigned char *)src;
	p_dest = (unsigned char *)dest;
	if (!n)
		return (dest);
	while (n--)
		*p_dest++ = *p_src++;
	return (dest);
}
