#ifndef PARSE_H
# define PARSE_H

// TOKEN OPTIONS
# define OR (1 << 0)
# define PIPE (1 << 1)
# define AND (1 << 2)
# define OUTPUT_REDIR_APPEND (1 << 3)
# define OUTPUT_REDIR (1 << 4)
# define HERE_DOC (1 << 5)
# define INPUT_REDIR (1 << 6)
# define OPEN_PARENTHESIS (1 << 7)
# define CLOSE_PARENTHESIS (1 << 8)

# define REDIR_OP (1 << 9)
# define PARENTHESIS (1 << 10)

# define WORD (1 << 11)
# define OPERATOR (1 << 12)
# define BUILTIN (1 << 13)
# define EMPTY_WORD (1 << 14)
# define EXPANDED_WORD (1 << 15)

// FRAGMENT TYPES
# define SINGLE 1
# define DOUBLE 2
# define UNQUOTED 3
# define EMPTY 4

// # include "libft/libft.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

typedef struct	s_fragment
{
	size_t	start;
	size_t	end;
	int		type;
	int		starts_with_space;
	int		ends_with_space;
}	t_fragment;

typedef struct	s_token
{
	char				*str;
	int					options;
	size_t				fragment_count;
	t_fragment			*fragments;
}	t_token;

typedef	struct	s_print_d
{
	char	**operators;
	t_token	*token;
	char	*line;
}	t_print_d;

typedef enum	e_bnode_type
{
	BNODE_COMMAND,
	BNODE_PIPE,
	BNODE_AND,
	BNODE_OR,
	BNODE_SUBSHELL
}	t_bnode_type;

typedef struct	s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	char			**cmd_argv;
	t_bnode_type	type;
}	t_btree;

/* TEMP print.c */
void	print_tokens(t_print_d *data);
void	print_btree_pyramid(const t_btree *node);

/* execute.c */
int		execute(t_btree *tree, t_bnode_type parent_type);

/* parse.c */
t_btree	*create_exec_tree(char *line, char **operators);
int		btoindex(int options);

/* validate_tokens.c */
int		validate_tokens(t_list *tokens, char **operators);
	
/* parse_utils.c */
int		create_operators(char ***operators);
void	free_split(char **arr);
int		is_operator(char *cur_char, char **operators);
void	print_line_arr(char **line_arr);
void	set_len_and_op(char *line_start, char **operators,
	size_t *substr_len, int *op_index);

/* tokenize.c */
int		add_token(t_list **head, t_token *token);
t_token	*create_token(void);
t_list	*tokenize(char *line, char **operators);

/* tokenize_utils.c */
void	skip_blank(char *line, size_t *i);
size_t	len_to_delimiter(char *line, char **operators);
size_t	len_to_unquoted_delimiter(char *line, char **operators);
size_t	len_to_quote_or_delimiter(char *line, char **operators);

/* fragment.c */
int		fragment_double_quote(char *line, t_token *token, size_t *i);
int		fragment_single_quote(char *line, t_token *token, size_t *i);
int		fragment_unquoted(char *line, t_token *token, size_t *i, char **operators);
int		handle_fragments(char *line, char **operators, t_token *token, size_t *i);

/* execution_tree.c */
t_btree	*create_tree(t_list *tokens);

//this will contain envp
typedef struct s_data
{
	char	**env;
	int		rt;
} t_data;


#endif
