/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:47:06 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/07/10 18:40:47 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_chunk
{
	char				*chunk;
	ssize_t				size;
	struct s_chunk		*next;
}	t_chunk;

char		*mk_line(char **line, ssize_t *line_len, t_chunk *c);
int			fix_chunk(t_chunk **node);
char		*omg(t_chunk **node, t_chunk *c, char *line);
char		*line_from_list(t_chunk **node);
char		*get_next_line(int fd);
ssize_t		has_nl(char *buffer, ssize_t bytes_read);
t_chunk		*lst_new(char *str, ssize_t bytes_read);
int			lstadd_back(t_chunk **lst, t_chunk *new);
void		lstclear(t_chunk **lst);
void		*ft_memcpy(void *dest, const void *src, ssize_t n);

#endif