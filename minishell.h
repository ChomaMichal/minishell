#ifndef MINISHELL_H
# define MINISHELL_H

//this contains ids of the child processes that are currently running
typedef struct s_ids
{
	struct s_ids	*next;
	int				pid;
}	t_ids;

//this will contain envp
typedef struct s_data
{
	char			**env;
	int				rt;
	t_ids			*pids;
	struct s_btree	*head;
	int				subshell;
}	t_data;

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

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>


/* DEV print.c */
void	btree_apply_suffix(t_btree *root, void (*applyf)(void *));
void	print_btree_pyramid(const t_btree *node);

/* parsing/parsing.c */
t_btree	*create_exec_tree(char *line, char **operators);
// int		btoindex(int options);

// execute
void	execute(t_btree *tree, t_data *data);

int		wait_and_get_exit_value(t_ids *list);
#endif
