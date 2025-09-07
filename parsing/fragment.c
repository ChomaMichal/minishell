#include "minishell.h"

int	fragment_double_quote(char *line, t_token *token, size_t *i)
{
	char	*match;
	size_t	len;

	match = ft_strchr(&line[*i + 1], '\"');
	if (!match)
		return (ft_printf(2, "minishell: unclosed quote `\"'\n"), 1); // LEAKS WHEN THIS CHECKS !!!!
	if (match == &line[*i + 1])
	{
		*i += 2;
		return (0);
	}
	len = match - &line[*i];
	token->fragments[token->fragment_count].start = *i + 1;
	token->fragments[token->fragment_count].end = *i + 1 + (match - &line[*i] - 2);
	token->fragments[token->fragment_count].type = DOUBLE;
	token->fragment_count += 1;
	// printf("start:(%zu) ==== end:(%zu)\n", *i + 1, *i + 1 + (match - &line[*i] - 2));
	*i += 1 + (match - &line[*i]);
	// printf("D -> incremented i to be at %c\n", line[*i]);
	return (0);
}

int	fragment_single_quote(char *line, t_token *token, size_t *i)
{
	char		*match;

	match = ft_strchr(&line[*i + 1], '\'');
	if (!match)
		return (ft_printf(2, "minishell: unclosed quote `\''\n"), 1);
	if (match == &line[*i + 1])
	{
		*i += 2;
		return (0);
	}
	token->fragments[token->fragment_count].start = *i + 1;
	token->fragments[token->fragment_count].end = *i + 1 + (match - &line[*i] - 2);
	token->fragments[token->fragment_count].type = SINGLE;
	token->fragment_count += 1;
	// printf("start:(%zu) ==== end:(%zu)\n", *i + 1, *i + 1 + (match - &line[*i] - 2));
	*i += 1 + (match - &line[*i]);
	// printf("S -> incremented i to be at %c\n", line[*i]);
	return (0);
}

int	fragment_unquoted(char *line, t_token *token, size_t *i, char **operators)
{
	size_t	unquoted_len;

	unquoted_len = len_to_quote_or_delimiter(&line[*i], operators);
	// printf("unquoted len is %zu\n", unquoted_len);
	token->fragments[token->fragment_count].start = *i;
	token->fragments[token->fragment_count].end = *i + unquoted_len - 1;
	token->fragments[token->fragment_count].type = UNQUOTED;
	token->fragment_count += 1;
	*i += unquoted_len;
	// printf("incremented i to be at %c\n", line[*i]);
	return (0);
}

int	handle_fragments(char *line, char **operators, t_token *token, size_t *i)
{
	size_t	token_len;

	token_len = len_to_unquoted_delimiter(&line[*i], operators);
	while(line[*i] && len_to_unquoted_delimiter(&line[*i], operators) > 0)
	{
		if (line[*i] == '\"')
		{
			if (fragment_double_quote(line, token, i))
				return (1);
		}
		else if (line[*i] == '\'')
		{
			if (fragment_single_quote(line, token, i))
				return (1);
		}
		else if (line[*i])
			if (fragment_unquoted(line, token, i, operators))
				return (1);
	}
	return (0);
}
