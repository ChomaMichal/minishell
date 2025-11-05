/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 18:41:19 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/05 17:39:21 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2025/10/29 12:45:44 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	add_here_node(t_here_doc **here_list, char *delimiter, t_btree *bnode)
{
	t_here_doc	*here_node;
	t_here_doc	*cur;

	here_node = malloc(sizeof(t_here_doc));
	if (!here_node)
		return (1);
	here_node->bnode = bnode;
	here_node->delimiter = ft_strdup(delimiter);
	here_node->file_name = NULL;
	if (!here_node->delimiter)
		return (free(here_node), 1);
	here_node->next = NULL;
	if (!*here_list)
		*here_list = here_node;
	else
	{
		cur = *here_list;
		while (cur->next)
			cur = cur->next;
		cur->next = here_node;
	}
	return (0);
}

static t_redir_list	*redir_list_last(t_redir_list *node)
{
	t_redir_list	*cur;

	cur = node;
	while (cur->next)
		cur = cur->next;
	return (cur);
}

t_redir_type	get_redir_type(int options)
{
	if (options & OUTPUT_REDIR)
		return (REDIR_OUT);
	else if (options & OUTPUT_REDIR_APPEND)
		return (REDIR_OUT_APP);
	else if (options & INPUT_REDIR)
		return (REDIR_IN);
	else if (options & HERE_DOC)
		return (REDIR_HERE);
	return (0);
}

int	add_redir_node(t_redir_list **redir_list, int options, char *file_name)
{
	t_redir_list	*new_node;
	t_redir_list	*cur;

	new_node = malloc(sizeof(t_redir_list));
	if (!new_node)
		return (1);
	new_node->type = get_redir_type(options);
	if (!(options & HERE_DOC))
	{
		new_node->file_name = ft_strdup(file_name);
		if (!new_node->file_name)
			return (free(new_node), 1);
	}
	else
		new_node->file_name = NULL;
	new_node->next = NULL;
	if (!*redir_list)
		*redir_list = new_node;
	else
		redir_list_last(*redir_list)->next = new_node;
	return (0);
}

void	clear_redir_list(t_redir_list **redir_list)
{
	t_redir_list	*cur;
	t_redir_list	*next;

	cur = *redir_list;
	while (cur)
	{
		next = cur->next;
		free(cur->file_name);
		free(cur);
		cur = next;
	}
	*redir_list = NULL;
}

void	clear_redir_list_unlink(t_redir_list **redir_list)
{
	t_redir_list	*cur;
	t_redir_list	*next;

	cur = *redir_list;
	while (cur)
	{
		next = cur->next;
		if (cur->type == REDIR_HERE)
			unlink(cur->file_name);
		free(cur->file_name);
		free(cur);
		cur = next;
	}
	*redir_list = NULL;
}

void	clear_here_list(t_here_doc **here_list)
{
	t_here_doc	*cur;
	t_here_doc	*next;

	cur = *here_list;
	while (cur)
	{
		next = cur->next;
		free(cur->delimiter);
		free(cur->file_name);
		free(cur);
		cur = next;
	}
	*here_list = NULL;
}

int	is_ambiguous_redir(t_list *tokens)
{
	t_list	*cur;
	size_t	expand_count;

	expand_count = 0;
	cur = tokens;
	if (cur->token->options & EMPTY_WORD)
		return (1);
	while (cur && cur->token->options & REDIR_WORD)
	{
		expand_count++;
		cur = cur->next;
	}
	if (expand_count > 1)
		return (1);
	return (0);
}

void	clear_all_redirs(t_btree *bnode, t_here_doc **here_list)
{
	clear_redir_list(&bnode->redir_list);
	clear_here_list(here_list);
}

int	create_redirections(t_list **tokens, t_btree *bnode, t_here_doc **here_list)
{
	t_list	*cur;

	cur = *tokens;
	while (cur && (cur->token->options & WORD
		|| cur->token->options & REDIR_OP))
	{
		if (cur->token->options & REDIR_OP)
		{
			if (is_ambiguous_redir(cur->next))
			{
				bnode->ambig = ft_strdup(cur->token->redir_word);
				if (!bnode->ambig)
					return (clear_all_redirs(bnode, here_list), 1);
			}
			if (add_redir_node(&bnode->redir_list, cur->token->options,
				cur->next->token->str))
				return (clear_all_redirs(bnode, here_list), 1);
			if (cur->token->options & HERE_DOC)
				if (add_here_node(here_list, cur->next->token->str, bnode))
					return (clear_all_redirs(bnode, here_list), 1);
			cur = cur->next;
		}
		cur = cur->next;
	}
	return (0);
}

char	*here_name(int *here_i)
{
	char	*name;
	char	*name_index;

	name_index = ft_itoa(*here_i);
	if (!name_index)
		return (NULL);
	name = ft_strjoin(".tmp", name_index); // RECHECK WHERE TO SAVE THE FILE!! ALSO CAN WE DO PIPE HERE_DOC LIKE BASH?
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

int	put_here_name(t_here_doc *here_node)
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

int	write_to_here_doc(char *delimiter, char *file_name, size_t *line_count)
{
	int		fd;
	char	*line;
	size_t	ln;

	ln = *line_count;
	// printf("%s filename\n", file_name);
	fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0777);
	if (fd < 0)
		return (close(fd), 1);
	while (sgnl == 0)
	{
		line = readline(">");
		if (sgnl == 1)
		{
			free(line);
			break;
		}
		if (!line)
		{
			ft_printf(2, "minishell: warning: here-document at line ");
			ft_printf(2, "%d delimited by end-of-file (wanted `%s')\n",
				ln, delimiter);
			return (0);
		}
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
			return (printf("here_name() failed\n"), 1);
		if (write_to_here_doc(cur->delimiter, cur->file_name, &d->line_count))
			return (printf("parse_here_doc() failed\n"), clear_here_list(here_list), 1);
		if (put_here_name(cur))
			return (printf("put_here_name() failed\n"), clear_here_list(here_list), 1);
		cur = cur->next;
	}
	return (0);
}

// int	open_write_here_docs(t_here_doc **here_list, t_parse_data *d)
// {
// 	int			here_i;
// 	int			here_fd;
// 	t_here_doc	*cur;
// 	char		*line;
// 	size_t		delimiter_len;

// 	//echo hi <<del1 <<del2 | echo<<del3 2ndcmd | <<del4 echo 3rd cmd | <<del5 echo <<del6 6th cmd <<del7
// 	cur = *here_list;
// 	here_fd = -1;
// 	here_i = 0;
// 	while (cur)
// 	{
// 		if (here_fd >= 0)
// 			close(here_fd);
// 		cur->file_name = here_name(&here_i);
// 		if (!cur->file_name)
// 			return (printf("here_name() failed\n"), clear_here_list(here_list), 1);

// 		cur->bnode->redir.here = ft_strdup(cur->file_name);
// 		cur = cur->next;
// 	}
// 	return (0);
// }
