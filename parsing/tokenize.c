/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 21:47:30 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/11/03 19:16:14 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	set_operator_options(int *options, int op_index, int *is_redir_word)
{
	*options |= (1 << op_index);
	*options |= OPERATOR;
	if (op_index == 3 || op_index == 4 || op_index == 5 || op_index == 6)
	{
		*options |= REDIR_OP;
		*is_redir_word = op_index;
	}
	else if (7 == op_index || op_index == 8)
		*options |= PARENTHESIS;
}

static int	handle_operator(t_parse_data *d, size_t *i, int *is_redir_word)
{
	t_token	*token;
	int		op_index;

	skip_spaces(d->line, i);
	op_index = is_operator(&d->line[*i], d->operators);
	if (op_index == -1)
		return (0);
	token = create_token(0);
	if (!token)
		return (palloc_err(), 1);
	set_operator_options(&token->options, op_index, is_redir_word);
	if (add_token(&d->tokens, token))
		return (free(token), 1);
	*i += ft_strlen(d->operators[op_index]);
	skip_spaces(d->line, i);
	op_index = is_operator(&d->line[*i], d->operators);
	if (op_index > -1)
		return (handle_operator(d, i, is_redir_word));
	return (0);
}

static int	handle_word(t_parse_data *d, size_t *i, int is_redir_word)
{
	t_token		*token;
	ssize_t		word_len;

	skip_spaces(d->line, i);
	token = create_token(is_redir_word);
	if (!token)
		return (palloc_err(), 1);
	token->options |= WORD;
	word_len = len_to_unquoted_delimiter(&d->line[*i], d->operators);
	if (word_len == 0)
		return (free(token), 0);
	token->fragments = malloc(sizeof(t_fragment)
			* count_fragments(&d->line[*i], word_len, d->operators));
	if (!token->fragments)
		return (free(token), palloc_err(), 1);
	token->str = ft_substr(&d->line[*i], 0, word_len);
	if (!token->str)
		return (free(token->fragments), free(token), palloc_err(), 1);
	if (handle_fragments(d->line, d->operators, token, i))
		return (free(token->fragments), free(token->str), free(token), 1);
	if (add_token(&d->tokens, token))
		return (free(token->fragments), free(token->str), free(token),
			palloc_err(), 1);
	return (0);
}

t_list	*tokenize(t_parse_data *d)
{
	int		is_redir_word;
	size_t	i;

	i = 0;
	d->tokens = NULL;
	is_redir_word = 0;
	while (d->line[i])
	{
		if (handle_operator(d, &i, &is_redir_word))
			return (del_tokens(d->tokens), NULL);
		if (handle_word(d, &i, is_redir_word))
			return (del_tokens(d->tokens), NULL);
		is_redir_word = 0;
	}
	return (d->tokens);
}
