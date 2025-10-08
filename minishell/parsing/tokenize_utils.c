#include "parsing.h"

int	is_blank(char c)
{
	return (c == ' ' || c == '	');
}

void	skip_blank(char *line, size_t *i)
{
	while (is_blank(line[*i]))
		*i += 1;
}

size_t	len_to_delimiter(char *line, char **operators)
{
	size_t	len;
	size_t	op;

	len = 0;
	while (line[len])
	{
		op = 0;
		if (line[len] == ' '|| line[len] == '	')
			return (len);
		while (operators[op])
		{
			if (!ft_strncmp(&line[len], operators[op], ft_strlen(operators[op])))
				return (len);
			op++;
		}
		len++;
	}
	return (len);
}

size_t	len_to_unquoted_delimiter(char *line, char **operators)
{
	size_t	len;
	size_t	op;
	int		in_quote;

	len = 0;
	in_quote = 0;
	while (line[len])
	{
		if (line[len] == '\"' && !in_quote)
			in_quote = 1;
		else if (line[len] == '\'' && !in_quote)
			in_quote = 2;
		else if ((line[len] == '\"' && in_quote == 1)
			|| (line[len] == '\'' && in_quote == 2))
			in_quote = 0;
		if (!in_quote)
		{
			op = 0;
			if (line[len] == ' '|| line[len] == '	')
				return (len);
			while (operators[op])
			{
				if (!ft_strncmp(&line[len], operators[op], ft_strlen(operators[op])))
					return (len);
				op++;
			}
		}
		len++;
	}
	return (len);
}

size_t	len_to_quote_or_delimiter(char *line, char **operators)
{
	size_t	len;
	size_t	op;

	len = 0;
	while (line[len])
	{
		op = 0;
		if (line[len] == ' '|| line[len] == '	'
			|| line[len] == '\'' || line[len] == '\"')
				return (len);
		while (operators[op])
		{
			if (!ft_strncmp(&line[len], operators[op], ft_strlen(operators[op])))
				return (len);
			op++;
		}
		len++;
	}
	return (len);
}
