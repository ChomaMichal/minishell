/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:30:29 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/06 14:42:38 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	print_here_warning(size_t ln, char *delimiter)
{
	ft_printf(2, "minishell: warning: here-document at line ");
	ft_printf(2, "%d delimited by end-of-file (wanted `%s')\n",
		ln, delimiter);
}

static char	*here_name(int *here_i)
{
	char	*name;
	char	*name_index;

	name_index = ft_itoa(*here_i);
	if (!name_index)
		return (NULL);
	name = ft_strjoin(".tmp", name_index);
	free(name_index);
	if (!name)
		return (NULL);
	if (access(name, F_OK) == 0)
	{
		*here_i += 1;
		return (free(name), here_name(here_i));
	}
	return (name);
}

static int	put_here_name(t_here_doc *here_node)
{
	t_redir_list	*cur;

	cur = here_node->bnode->redir_list;
	while (cur)
	{
		if (cur->type == REDIR_HERE && cur->file_name == NULL)
			break ;
		cur = cur->next;
	}
	if (cur && cur->file_name == NULL)
	{
		cur->file_name = ft_strdup(here_node->file_name);
		if (!cur->file_name)
			return (1);
	}
	return (0);
}

static int	write_to_here_doc(char *delimiter, char *file_name,
	size_t *line_count)
{
	int		fd;
	char	*line;
	size_t	ln;

	ln = *line_count;
	fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0777);
	if (fd < 0)
		return (close(fd), 1);
	while (1)
	{
		line = readline(">");
		if (sgnl != 0)
			return (close(fd), free(line), 1);
		if (!line)
			return (print_here_warning(ln, delimiter), 0);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == 0)
			return (free(line), close(fd), 0);
		(write(fd, line, ft_strlen(line)), write(fd, "\n", 1), free(line));
		*line_count += 1;
	}
	return (close(fd), 0);
}

int	open_write_here_docs(t_here_doc **here_list, t_parse_data *d)
{
	int				here_i;
	t_here_doc		*cur;
	t_redir_list	*redir_node;

	here_i = 0;
	cur = *here_list;
	while (cur)
	{
		cur->file_name = here_name(&here_i);
		if (!cur->file_name)
			return (1);
		if (write_to_here_doc(cur->delimiter, cur->file_name, &d->line_count))
			return (clear_here_list(here_list), 1);
		if (put_here_name(cur))
			return (clear_here_list(here_list), 1);
		cur = cur->next;
	}
	return (0);
}
