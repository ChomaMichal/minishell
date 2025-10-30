/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchoma <your@mail.com>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:05:49 by mchoma            #+#    #+#             */
/*   Updated: 2025/10/30 16:44:23 by mchoma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static int	open_dup2_in(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "open failed in redirection\n"), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (ft_printf(2, "dup2 failed in redirection\n"), -1);
	close(fd);
	return (1);
}

static int	open_dup2_out_append(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "open failed in redirection\n"), -1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (ft_printf(2, "dup2 failed in redirection\n"), -1);
	close(fd);
	return (1);
}

static int	open_dup2_out_truncate(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf(2, "open failed in redirection\n"), -1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (ft_printf(2, "dup2 failed in redirection\n"), -1);
	close(fd);
	return (1);
}

int	redir_dup2(t_btree *tree)
{
	t_redir_list	*cur;
	int				err;

	cur = tree->redir_list;
	while (cur)
	{
		if (cur->type == REDIR_HERE || cur->type == REDIR_IN)
			err = open_dup2_in(cur->file_name);
		else if (cur->type == REDIR_OUT)
			err = open_dup2_out_truncate(cur->file_name);
		else if (cur->type == REDIR_OUT_APP)
			err = open_dup2_out_append(cur->file_name);
		cur = cur->next;
		if (err == -1)
			return (-1);
	}
	return (0);
}
