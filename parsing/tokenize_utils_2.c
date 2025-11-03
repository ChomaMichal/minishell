/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:42:35 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/03 18:53:00 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_double_quote(size_t *count, ssize_t *i, ssize_t word_len,
	char *line)
{
	*count += 1;
	*i += 1;
	while (*i < word_len && line[*i] != '\"')
		*i += 1;
	if (*i == word_len)
		return (1);
	*i += 1;
	return (0);
}

static int	count_single_quote(size_t *count, ssize_t *i, ssize_t word_len,
	char *line)
{
	*count += 1;
	*i += 1;
	while (*i < word_len && line[*i] != '\'')
		*i += 1;
	if (*i == word_len)
		return (1);
	*i += 1;
	return (0);
}

int	add_token(t_list **head, t_token *token)
{
	t_list	*node;

	node = ft_lstnew(token);
	if (!node)
		return (palloc_err(), 1);
	ft_lstadd_back(head, node);
	return (0);
}

t_token	*create_token(int is_redir_word)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->fragment_count = 0;
	token->fragments = NULL;
	token->options = 0;
	if (is_redir_word == 5)
		token->options |= HERE_DEL_WORD;
	else if (is_redir_word)
		token->options |= REDIR_WORD;
	token->str = NULL;
	token->redir_word = NULL;
	token->fragment_i = 0;
	token->stars_arr = NULL;
	return (token);
}

size_t	count_fragments(char *line, ssize_t word_len, char **operators)
{
	size_t	count;
	ssize_t	i;

	count = 0;
	i = 0;
	while (i < word_len)
	{
		if (line[i] == '\"')
		{
			if (count_double_quote(&count, &i, word_len, line))
				return (count);
		}
		else if (line[i] == '\'')
		{
			if (count_single_quote(&count, &i, word_len, line))
				return (count);
		}
		else
		{
			count++;
			i += len_to_quote_or_delimiter(&line[i], operators);
		}
	}
	return (count);
}
