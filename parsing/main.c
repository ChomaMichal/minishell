#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("josef-shell-$ ");
		if (!line || ft_strncmp(line, "end", 4) == 0)
			break ;
		if (line[0])
			add_history(line);
		// rl_line_buffer[1] = 'x';
		printf("line read is \"%s\"\n", line);
		rl_on_new_line();
		free(line);
	}
	printf("exit\n");
	return (0);
}
