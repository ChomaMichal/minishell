#include "minishell.h"

int	wrong_first_token(t_list *cur, char **operators)
{
	int	options;

	options = cur->token->options;
	if (options & OR || options & AND || options & PIPE
		|| options & CLOSE_PARENTHESIS)
		{
			ft_printf(2, "minishell: syntax error near unexpected token `%s'\n", 
				operators[btoindex(options)]);			
			return (1);
		}
	return (0);
}

int	validate_and_or(t_list *cur, char **operators)
{
	if (cur->next == NULL)
	{
		ft_printf(2, "minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (cur->next->token->options & AND
		|| cur->next->token->options & OR
		|| cur->next->token->options & PIPE
		|| cur->next->token->options & CLOSE_PARENTHESIS)
	{
		ft_printf(2, "minishell: syntax erorr near unexpected token `%s'\n",
			operators[btoindex(cur->next->token->options)]);
		return (1);
	}
	return (0);
}

int	validate_redir(t_list *cur, char **operators)
{
	if (!cur->next)
		return (ft_printf(2, "minishell: syntax error near unexpected token `newline'\n"), 1);
	if (!(cur->next->token->options & WORD))
	{
		ft_printf(2, "minishell: syntax error near unexpected token `%s'\n",
			operators[btoindex(cur->next->token->options)]);
		return (1);
	}
	return (0);
}

int	validate_open_paren(t_list *cur, long *paren_count, char **operators)
{
	if (cur->next == NULL)
	{
		ft_printf
		(2, "minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	*paren_count += 1;
	if (cur->next->token->options & AND
		|| cur->next->token->options & OR
		|| cur->next->token->options & PIPE
		|| cur->next->token->options & CLOSE_PARENTHESIS)
	{
		ft_printf(2, "minishell: syntax erorr near unexpected token `%s'\n",
			operators[btoindex(cur->next->token->options)]);
		return (1);
	}		
	return (0);
}

int	validate_close_paren(t_list *cur, long *paren_count)
{
	if (*paren_count == 0)
	{
		ft_printf(2, "minishell: syntax error near unexpected token `)'\n");
		return (1);
	}
	*paren_count -= 1;
	if (cur->next && cur->next->token->options & WORD)
	{
		ft_printf(2, "minishell: syntax error near unexpected token `%s'\n",
			cur->next->token->str);
		return (1);
	}
	if (cur->next && cur->next->token->options & OPEN_PARENTHESIS)
	{
		ft_printf(2, "minishell: syntax error near unexpected token `('\n");
		return (1);
	}
	return (0);
}

int	validate_paren(t_list *cur, long *paren_count, char **operators)
{
	if (cur->token->options & OPEN_PARENTHESIS)
		return (validate_open_paren(cur, paren_count, operators));
	else if (cur->token->options & CLOSE_PARENTHESIS)
		return (validate_close_paren(cur, paren_count));
	return (ft_printf(2, "SOMETHING WRONG (validate_paren())\n"), 0);
}

int	validate_pipe(t_list *cur, char **operators)
{
	if (cur->next == NULL)
	{
		ft_printf(2, "minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (cur->next->token->options & AND
		|| cur->next->token->options & OR
		|| cur->next->token->options & PIPE
		|| cur->next->token->options & CLOSE_PARENTHESIS)
	{
		ft_printf(2, "minishell: syntax error near unexpected token `%s'\n",
			operators[btoindex(cur->next->token->options)]);
		return (1);
	}
	return (0);
}

int	validate_word(t_list *cur)
{
	if (cur->next && cur->next->token->options & OPEN_PARENTHESIS)
	{
		ft_printf(2, "minishell: syntax error near unexpected token `('\n");
		return (1);
	}
	return (0);
}

int	validate_tokens(t_list *tokens, char **operators)
{
	t_list	*cur;
	int		options;
	long	paren_count;

	paren_count = 0;
	cur = tokens;
	if (tokens && wrong_first_token(cur, operators))
		return (1);
	while (cur)
	{
		options = cur->token->options;
		if (((options & OR || options & AND) && validate_and_or(cur, operators))
			|| (options & REDIR_OP && validate_redir(cur, operators))
			|| (options & PARENTHESIS && validate_paren(cur, &paren_count, operators))
			|| (options & PIPE && validate_pipe(cur, operators))
			|| (options & WORD && validate_word(cur)))
			return (1);
		cur = cur->next;
	}
	if (paren_count > 0)
	{
		ft_printf(2, "minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}
