/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:54:13 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/05 13:57:12 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	del_token(void *ptr)
{
	free(((t_token *)ptr)->fragments);
	free(((t_token *)ptr)->str);
	free(((t_token *)ptr)->redir_word);
	free(((t_token *)ptr)->stars_arr);
	free(ptr);
}

void	del_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, del_token);
}

int	is_operator(char *line_start, char **operators)
{
	size_t	i;

	i = 0;
	while (operators[i])
	{
		if (ft_strncmp(line_start, operators[i], ft_strlen(operators[i])) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	set_len_and_op(char *line_start, char **operators,
	size_t *substr_len, int *op_index)
{
	size_t	len;

	len = 0;
	*op_index = is_operator(&line_start[len], operators);
	while (line_start[len] && *op_index == -1)
	{
		len += 1;
		*op_index = is_operator(&line_start[len], operators);
	}
	*substr_len = len;
}

void	parse_set_rt(t_parse_data *d, int rt)
{
	d->data->rt = rt;
}
