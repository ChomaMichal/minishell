#include "minishell.h"

int	main(void)
{
	char	*line;
	t_btree	*cmds_tree;

	while (1)
	{
		line = readline("josef-shell-$ ");
		if (!line)
			break ;
		if (line[0])
			add_history(line);
		rl_on_new_line();
		// printf("line read is \"%s\"\n", line);
		cmds_tree = create_cmds_tree(line);
		// rl_line_buffer[1] = 'x';
		free(line);
	}
	printf("exit\n");
	return (0);
}
