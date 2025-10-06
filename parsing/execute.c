#include "minishell.h"

// int	child_process(t_btree *tree)
// {
// 	printf(">>>%s\n", tree->cmd_argv[0]);
// 	execve(tree->cmd_argv[0], &tree->cmd_argv[1], __environ);
// 	return (0);
// }

int	execute_pipeline(t_btree *left, t_btree *right, pid_t pipe_fd[2])
{
	__pid_t	pid_1;
	__pid_t	pid_2;

	pid_1 = fork();
	if (pid_1 == 0)
	{
		printf("pid_1 is dupping (%d) to (%d)\n", pipe_fd[1], STDOUT_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		printf("executed first command\n");
		execve(left->cmd_argv[0], right->cmd_argv, __environ);
		exit(0);
	}
	pid_2 = fork();
	if (pid_2 == 0)
	{
		printf("pid_2 is dupping (%d) to (%d)\n", pipe_fd[0], STDIN_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(open("output", O_WRONLY), STDOUT_FILENO);
		execve(right->cmd_argv[0], right->cmd_argv, __environ);
		exit(0);
	}
	wait(NULL);
	// wait(NULL);
	close(pipe_fd[1]);
	close(pipe_fd[0]);
	// wait(NULL);
	return (0);
}

// void	execute_node(void *ptr)
// {
// 	t_btree	*node;

// 	node = (t_btree *)ptr;
// 	if (node->type == BNODE_PIPE)
// 	{
		
// 	}
// 	node->
// }

typedef struct	s_exec_data
{
	t_bnode_type	parent_type;
}	t_exec_data;

void	sbtree_apply_suffix(t_btree *root, void (*applyf)(void *), t_exec_data data)
{
	data.parent_type = root->type;
	if (root->left)
		sbtree_apply_suffix(root->left, applyf, data);
	if (root->right)
		sbtree_apply_suffix(root->right, applyf, data);
	applyf(root);
}

void	func(void *ptr)
{
	;
}

int	execute(t_btree *tree, t_bnode_type parent_type)
{
	int	pipe_fd[2];

	// char	*cmd_1 = ft_strsjoin(tree->left->cmd_argv[0], " ", tree->left->cmd_argv[1]);
	// char	*cmd_2 = ft_strsjoin(tree->right->cmd_argv[0], " ", tree->right->cmd_argv[1]);
	// int		input_fd = open("input", O_RDONLY);
	// int		output_fd = open("output", O_RDWR);
	// // dup2(STDOUT_FILENO, output_fd);
	// char	**pipex_arr = malloc(sizeof (char *) * 6);

	// pipex_arr[0] = ft_strdup("./pipex_bonus");
	// pipex_arr[1] = ft_strdup("input");
	// pipex_arr[2] = cmd_1;
	// pipex_arr[3] = cmd_2;
	// pipex_arr[4] = ft_strdup("output");
	// pipex_arr[5] = NULL;
	t_exec_data	data;

	data.parent_type = parent_type;
	sbtree_apply_suffix(tree, func, data);
	// pid_t	pid = fork();
	// if (pid == 0)
	// 	execve(pipex_arr[0], pipex_arr, __environ);
	// wait(NULL);
	// pipe(pipe_fd);
	// if (tree->type == BNODE_PIPE)
	// 	execute_pipeline(tree->left, tree->right, pipe_fd);
	return (0);
}