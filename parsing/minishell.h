#ifndef MINISHELL_H
# define MINISHELL_H

# define OR (1 << 0)
# define PIPE (1 << 1)
# define AND (1 << 2)
# define OUTPUT_REDIR_APPEND (1 << 3)
# define OUTPUT_REDIR (1 << 4)
# define HERE_DOC (1 << 5)
# define INPUT_REDIR (1 << 6)
# define OPEN_PARENTHESIS (1 << 7)
# define CLOSE_PARENTHESIS (1 << 8)
# define SINGLE_QUOTE (1 << 9)
# define DOUBLE_QUOTE (1 << 10)

# define WORD (1 << 11)
# define OPERATOR (1 << 12)
# define BUILTIN (1 << 13)

# define EMPTY 0
# define SINGLE 1
# define DOUBLE 2
# define UNQUOTED 3

# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <stdio.h>

/* parse.c */
t_btree	*create_cmds_tree(char *line, char **operators);

/* parse_utils.c */
int		create_operators(char ***operators);
void	free_split(char **arr);
int		is_operator(char *cur_char, char **operators);
void	print_line_arr(char **line_arr);
void	set_len_and_op(char *line_start, char **operators,
	size_t *substr_len, int *op_index);

/* tree.c */
int		has_bigger_index(void *cur_item, void *inserted_item);
void	print_node_info(void *node);
t_bitem	*create_item(char *str, int index);
void	free_item(t_bitem *item);
t_btree	*create_cmds_tree_test(t_bitem *item[5]);
void	free_btree_node(void *ptr);

#endif