#ifndef MINISHELL_H
#define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>
# include <stdio.h>

t_btree	*create_cmds_tree(char *line);

#endif