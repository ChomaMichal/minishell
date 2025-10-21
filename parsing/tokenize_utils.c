/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-ghna <jel-ghna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 15:59:58 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/10/21 23:37:19 by jel-ghna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_delimiter(char *line, char **operators)
{
	int	op_index;

	op_index = 0;
	if (*line == ' ' || *line == '	')
		return (1);
	while (operators[op_index])
	{
		if (!ft_strncmp(line, operators[op_index],
				ft_strlen(operators[op_index])))
			return (1);
		op_index++;
	}
	return (0);
}

size_t	count_fragments(char *line, ssize_t word_len, char **operators)
{
	size_t	count;
	ssize_t	i;
	char	*found;

	count = 0;
	i = 0;
	while (i < word_len)
	{
		if (line[i] == '\"')
		{
			count++;
			found = ft_strchr(&line[i + 1], '\"');
			if (!found)
				return (count);
			i += found - (line + 1);
		}
		else if (line[i] == '\'')
		{
			count++;
			found = ft_strchr(&line[i + 1], '\'');
			if (!found)
				return (count);
			i += found - (line + 1);
		}
		else
		{
			count++;
			i += len_to_quote_or_delimiter(&line[i], operators);
		}
		i++;
	}
	
	i = -1;
	while (++i < word_len)
	{
		// printf("reading (%c) index (%zi)\n", line[i], i);
		if (line[i] == '\"' && ft_strchr(&line[i + 1], '\"'))
		{
			printf("if (\")\n");
			count++;
			i += (ft_strchr(&line[i + 1], '\"') - &line[i]);
		}
		else if (line[i] == '\'' && ft_strchr(&line[i + 1], '\''))
		{
			printf("if (\')\n");
			count++;
			i += (ft_strchr(&line[i + 1], '\'') - &line[i]);
		}
		else
		{
			count++;
			printf("else\n");
			// printf("added %zi to i from else\ndelimiter is %c\n", len_to_quote_or_delimiter(&line[i], operators), line[i + len_to_quote_or_delimiter(&line[i], operators)]);
			i += len_to_quote_or_delimiter(&line[i], operators);
		}
		// printf("i is now %zi\n", i);
	}
	printf("counted %zi fragments\n", count);
	return (count);
}

void	skip_spaces(char *line, size_t *i)
{
	while (line[*i] == ' ' || line[*i] == '	')
		*i += 1;
}
ssize_t	len_to_unquoted_delimiter(char *line, char **operators)
{
	ssize_t	len;
	int		in_quote;

	len = 0;
	in_quote = 0;
	while (line[len])
	{
		if (line[len] == '\"' && !in_quote)
			in_quote = 1;
		else if (line[len] == '\'' && !in_quote)
			in_quote = 2;
		else if (((line[len] == '\"' && in_quote == 1)
				|| (line[len] == '\'' && in_quote == 2)))
			in_quote = 0;
		if (!in_quote)
			if (is_delimiter(&line[len], operators))
				return (len);
		len++;
	}
	return (len);
}

ssize_t	len_to_quote_or_delimiter(char *line, char **operators)
{
	ssize_t	len;
	size_t	op;

	len = 0;
	while (line[len])
	{
		op = 0;
		if (line[len] == ' ' || line[len] == '	'
			|| line[len] == '\'' || line[len] == '\"')
			return (len);
		while (operators[op])
		{
			if (!ft_strncmp(&line[len], operators[op],
					ft_strlen(operators[op])))
				return (len);
			op++;
		}
		len++;
	}
	return (len);
}
