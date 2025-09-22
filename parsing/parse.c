#include "minishell.h"
// x &= ~(1 << 2)
// 000101
// 111011
//=000001

// DON't FORGET FUNCHECK

// #include <fcntl.h>
// void	signal_handler(int sig)
// {
// 	int fd = open("test", O_RDWR);
// 	write(fd, "sig recieved\n", 13);
// 	exit(1);
// 	// printf("sig recieved\n");
// }

// What if we have 2 bits of 2, and we want to check the 1 bit that is to the left?
// we read the one to the right first, which is an incorrect result.
// when calling it for token types, this function only works up to bit 8 (CLOSE_PAREN). Bigger is undefined.
//		||
//		||
//		\/
int	btoindex(int options)
{
	int	i;

	i = 0;
	while (!((options >> i) & 1))
		i++;
	return (i);
}

char	*create_dollar_sub(char *str, size_t *i)
{
	size_t	j;
	char	*sub;
	char	*env_value;

	j = 0;
	if (str[j] == '$')
		return (*i += 1, ft_strdup("$$"));
	if (str[j] == 0 || (!ft_isalpha(str[j]) && str[j] != '_'))
		return (ft_strdup("$"));
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	*i += j;
	sub = ft_substr(str, 0, j);
	if (!sub)
		return (NULL);
	env_value = getenv(sub);
	free(sub);
	if (!env_value)
		return (ft_strdup(""));
	env_value = ft_strdup(env_value);
	return (env_value);
}

char	*expand_quoted_fragment(char *line, char *fragment_str)
{
	char	*expanded_fragment;
	char	*sub_str;
	char	*tmp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	expanded_fragment = ft_strdup("");
	if (!expanded_fragment)
		return (NULL);
	while (fragment_str[j])
	{
		if (fragment_str[j] == '$')
		{
			fragment_str[j] = 0;
			tmp = ft_strjoin(expanded_fragment, &fragment_str[i]);
			free(expanded_fragment);
			if (!tmp)
				return (NULL);
			expanded_fragment = tmp;
			i = j + 1;
			sub_str = create_dollar_sub(&fragment_str[i], &i);
			if (!sub_str)
				return (NULL);
			tmp = ft_strjoin(expanded_fragment, sub_str);
			(free(expanded_fragment), free(sub_str));
			if (!tmp)
				return (NULL);
			expanded_fragment = tmp;
			j = i;
		}
		else
			j++;
	}
	tmp = ft_strjoin(expanded_fragment, &fragment_str[i]);
	free(expanded_fragment);
	expanded_fragment = tmp;
	return (expanded_fragment);
}

char	*expand_fragment(char *line, t_fragment fragment)
{
	char	*res;
	char	*fragment_str;

	res = NULL;
	fragment_str = ft_substr(line, fragment.start,
		fragment.end - fragment.start + 1);
	if (!fragment_str)
		return (NULL);
	if (fragment.type == SINGLE)
		res = fragment_str;
	else if (fragment.type == DOUBLE)
	{
		res = expand_quoted_fragment(line, fragment_str);
		free(fragment_str);
	}
	else if (fragment.type == UNQUOTED)
	{
		res = expand_quoted_fragment(line, fragment_str);
		free(fragment_str);
	}
	return (res);
}

int	expand_word(char *line, t_token *token)
{
	size_t	i;
	char	*expanded_word;
	char	*expanded_fragment;
	char	*tmp;

	i = 0;
	expanded_word = ft_strdup("");
	if (!expanded_word)
		return (1);
	while (i < token->fragment_count)
	{
		expanded_fragment = expand_fragment(line, token->fragments[i]);
		if (!expanded_fragment)
			return (free(expanded_word), 1);
		tmp = ft_strjoin(expanded_word, expanded_fragment);
		(free(expanded_word), free(expanded_fragment));
		if (!tmp)
			return (1);
		expanded_word = tmp;
		i++;
	}
	ft_printf(2, "expanded (%s) ", token->str);
	free(token->str);
	token->str = expanded_word;
	ft_printf(2, "to (%s)\n", token->str);
	return (0);
}

int	expand(t_list *tokens, char *line, char **operators)
{
	t_list	*cur;

	cur = tokens;
	while (cur)
	{
		if (cur->token->options & WORD)
			if (expand_word(line, cur->token))
				return (ft_printf(2, "malloc failed in expand_token() token: (%s)\n", cur->token->str), 1);
		cur = cur->next;
	}
	return (0);
}

void	delete_token(void *ptr)
{
	free(((t_token *)ptr)->fragments);
	free(((t_token *)ptr)->str);
	free(ptr);
}

void	free_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, delete_token);
}

t_btree	*create_exec_tree(char *line, char **operators)
{
	t_btree		*cmds_tree;
	t_list		*tokens;
	t_print_d	data;

	data.line = line;
	data.operators = operators;
	tokens = tokenize(line, operators);
	if (!tokens)
		return (ft_printf(2, "minishell: tokenize() failed\n"), NULL);
	if (validate_tokens(tokens, operators))
		return (ft_printf(2, "minishell: validate_tokens() failed\n"), free_tokens(tokens), NULL);
	if (expand(tokens, line, operators))
		return (ft_printf(2, "minishell: parse() failed\n"), free_tokens(tokens), NULL);
	// ft_lstiter(tokens, print_tokens, &data);
	cmds_tree = create_tree(tokens);
	free_tokens(tokens);
	return (cmds_tree);
	// return (cmds_tree);
}
