/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fragment_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josefelghnam <josefelghnam@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:06:53 by jel-ghna          #+#    #+#             */
/*   Updated: 2025/10/31 00:20:49 by josefelghna      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	copy_old_stars_arr(int *old_arr, int *new_arr, size_t old_len)
{
	size_t	i;

	i = 0;	
	if (!old_arr || old_len == 0)
		return ;
	while (i < old_len)
	{
		new_arr[i] = old_arr[i];
		i++;
	}
}

int	dont_mark_stars(t_list *target_node, size_t old_len, char *tmp)
{
	int	*stars_arr;

	stars_arr = ft_calloc(sizeof(int) * ft_strlen(tmp), 1);
	if (!stars_arr)
		return (1);
	copy_old_stars_arr(target_node->token->stars_arr, stars_arr, old_len);
	free(target_node->token->stars_arr);
	target_node->token->stars_arr = stars_arr;
	return (0);
}

int	mark_stars(t_list *target_node, size_t old_len, char *tmp)
{
	int	*stars_arr;

	stars_arr = ft_calloc(sizeof(int) * ft_strlen(tmp), 1);
	if (!stars_arr)
		return (1);
	copy_old_stars_arr(target_node->token->stars_arr, stars_arr, old_len);
	while (tmp[old_len])
	{
		if (tmp[old_len] == '*')
			stars_arr[old_len] = 1;
		old_len++;
	}
	free(target_node->token->stars_arr);
	target_node->token->stars_arr = stars_arr;
	return (0);
}

char	*create_var_val(char *str, size_t *start, t_expansion_data *xd)
{
	size_t	j;
	char	*key;
	char	*value;

	j = 0;
	if (str == 0 && !(xd->i + 1 == xd->token_node->token->fragment_count))
		return(ft_strdup(""));
	if (str[j] == '*')
		return (*start += 1, ft_strdup(""));
	if (str[j] == '$')
		return (*start += 1, ft_strdup("$$"));
	if (str[j] == '?')
		return (*start += 1, ft_itoa(xd->d->data->rt));
	if (str[j] == 0 || (!ft_isalpha(str[j]) && str[j] != '_'))
		return (ft_strdup("$"));
	while (ft_isalnum(str[j]) || str[j] == '_')
		j++;
	*start += j;
	key = ft_substr(str, 0, j);
	if (!key)
		return (NULL);
	value = ft_get_env_value(xd->d->data->env, key);
	free(key);
	return (value);
}

char	*safe_strjoin(char **str, char *str2, int free_second_str)
{
	char	*tmp;

	tmp = ft_strjoin(*str, str2);
	free(*str);
	if (free_second_str)
		free(str2);
	if (!tmp)
		return (NULL);
	*str = tmp;
	return (*str);
}

int	append_substr(t_list *target_node, char *str, int free_second_str, int double_quote)
{
	char	*tmp;
	size_t	old_len;

	old_len = ft_strlen(target_node->token->str);
	tmp = ft_strjoin(target_node->token->str, str);
	if (free_second_str)
		free(str);
	if (!tmp)
		return (1);
	if (!double_quote && dont_mark_stars(target_node, old_len, tmp))
		return (free(tmp), 1);
	else if (double_quote && mark_stars(target_node, old_len, tmp))
		return (free(tmp), 1);
	free(target_node->token->str);
	target_node->token->str = tmp;
	return (0);
}
