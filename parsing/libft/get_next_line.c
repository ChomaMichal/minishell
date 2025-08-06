/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:47:04 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/07/10 18:42:42 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*mk_line(char **line, ssize_t *line_len, t_chunk *c)
{
	char	*res;
	ssize_t	cpy_len;

	cpy_len = has_nl(c->chunk, c->size) + 1;
	if (cpy_len == 0)
		cpy_len = c->size;
	res = malloc((cpy_len + *line_len + 1) * sizeof(char));
	if (!res)
		return (free(res), NULL);
	ft_memcpy(res, *line, *line_len);
	free(*line);
	ft_memcpy(res + *line_len, c->chunk, cpy_len);
	*line_len = *line_len + cpy_len;
	res[*line_len] = 0;
	return (res);
}

int	fix_chunk(t_chunk **node)
{
	char	*tmp;
	size_t	new_size;
	t_chunk	*c;

	new_size = (*node)->size - (has_nl((*node)->chunk, (*node)->size) + 1);
	if (!new_size)
	{
		c = (*node)->next;
		return (lstclear(node), (*node) = c, 1);
	}
	tmp = malloc(new_size * sizeof(char));
	if (!tmp)
		return (lstclear(node), 0);
	ft_memcpy(tmp, (*node)->chunk + (*node)->size - new_size, new_size);
	free((*node)->chunk);
	(*node)->chunk = tmp;
	(*node)->size = new_size;
	return (1);
}

char	*omg(t_chunk **node, t_chunk *c, char *line)
{
	*node = c;
	if (!fix_chunk(node))
		return (lstclear(node), free(line), NULL);
	return (line);
}

char	*line_from_list(t_chunk **node)
{
	t_chunk	*c;
	t_chunk	*tmp;
	char	*line;
	ssize_t	line_len;
	ssize_t	nl;

	c = *node;
	line_len = 0;
	line = NULL;
	while (c)
	{
		nl = has_nl(c->chunk, c->size);
		line = mk_line(&line, &line_len, c);
		if (!line)
			return (lstclear(node), free(line), NULL);
		tmp = c->next;
		if (nl > -1)
			return (omg(node, c, line));
		*node = c->next;
		free(c->chunk);
		free(c);
		c = tmp;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_chunk	*node[128];
	t_chunk			*tmp;
	char			*buffer;
	ssize_t			bytes_read;

	tmp = node[fd];
	buffer = malloc(BUFFER_SIZE);
	while (tmp && (tmp)->chunk)
	{
		if (has_nl((tmp)->chunk, (tmp)->size) > -1)
			return (free(buffer), line_from_list(&node[fd]));
		tmp = tmp->next;
	}
	bytes_read = (buffer != NULL) * read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		if (!lstadd_back(&node[fd], lst_new(buffer, bytes_read)))
			return (free(buffer), lstclear(&node[fd]), NULL);
		if (has_nl(buffer, bytes_read) > -1)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (free(buffer), lstclear(&node[fd]), NULL);
	return (free(buffer), line_from_list(&node[fd]));
}

// #include <string.h>
// #include <stddef.h>
// #include <fcntl.h>
// #include <stdint.h>

// int	main(void)
// {
// 	int		fd;
// 	// int		file2;
// 	char	*line;
// 	// char	*diff_line;

// 	fd = open("test", O_RDWR);
// 	// file2 = open("test2", O_RDWR);
// 	while ((line = get_next_line(fd)))
// 	{
// 		write(1, line, strlen(line));//(">>>%s", line);
// 		// diff_line = get_next_line(file2);
// 		// write(1, diff_line, strlen(diff_line));
// 		// free(diff_line);
// 		free(line);
// 	}
// 	// while ((diff_line = get_next_line(file2)))
// 	// {
// 	// 	write(1, diff_line, strlen(diff_line));
// 	// 	free(diff_line);
// 	// }
// 	return (0);
// }
