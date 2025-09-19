#include "minishell.h"

void	rec_print_bits(int x, int i)
{
	if (i < 31)
		rec_print_bits(x, i + 1);
	if ((x >> i) & 1)
		write(1, "1", 1);
	else
		write(1, "0", 1);
	if (!(i % 8) && i != 0)
		write(1, ",", 1);
	if (!(i % 4) && i != 0)
		write(1, " ", 1);
	if (i == 32)
		write(1, "\n", 1);
}

void	print_bits(int x, int i)
{
	printf("options: ");
	fflush(NULL);
	printf("\n");
	rec_print_bits(x, i);
}

void	print_fragment_type(t_fragment *fragment)
{
	if (fragment->type == SINGLE)
		write(1, "	SINGLE QUOTE", 14);
	else if (fragment->type == DOUBLE)
		write(1, "	DOUBLE QUOTE", 14);
	else if (fragment->type == UNQUOTED)
		write(1, "	UNQUOTED", 10);
}

int	token_count = 0;
void	print_tokens(t_print_d *data)
{
	char		**operators;
	t_token		*token;
	char		*line;
	t_fragment	fragment;
	size_t		i;
	size_t		len;

	i = 0;
	operators = data->operators;
	token = data->token;
	line = data->line;
	if (token->options & WORD)
	{
		printf("token (%d) type: (WORD)\n", token_count++);
		if (token->fragment_count == 0)
			printf("[%s] EMPTY WORD\n", token->str);
		while (i < token->fragment_count)
		{
			fragment = (token->fragments)[i];
			len = fragment.end - fragment.start + 1;
			write(1, "[", 1);
			write(1, &line[fragment.start], len);
			write(1, "]", 1);
			if (len)
				print_fragment_type(&fragment);
			write(1, "\n", 1);
			i++;
		}
	}
	else if (token->options & OPERATOR)
	{
		printf("token (%d) type: (OPERATOR)\n", token_count++);		
		printf("[%s]\n", operators[btoindex(token->options)]);
	}
	// print_bits(token->options, 0);
	printf("\n\n");
	// free(token->fragments);
}

const char *bnode_type_to_str(t_bnode_type type)
{
    if (type == BNODE_COMMAND) return "CMD";
    if (type == BNODE_PIPE) return "|";
    if (type == BNODE_AND) return "&&";
    if (type == BNODE_OR) return "||";
    if (type == BNODE_SUBSHELL) return "()";
    return "?";
}

void print_cmd(const t_btree *node)
{
    if (node->type == BNODE_COMMAND && node->cmd_argv)
    {
        for (int i = 0; node->cmd_argv[i]; i++)
            printf("%s ", node->cmd_argv[i]);
    }
    else
    {
        printf("%s", bnode_type_to_str(node->type));
    }
}

char *get_label(const t_btree *node)
{
    static char buf[256];

    if (node->type == BNODE_COMMAND && node->cmd_argv)
    {
        buf[0] = '\0';
        for (int i = 0; node->cmd_argv[i]; i++)
        {
            strcat(buf, node->cmd_argv[i]);
            strcat(buf, " ");
        }
        return buf;
    }
    return (char *)bnode_type_to_str(node->type);
}

/* ---------- Drawing ---------- */
void print_ascii_tree(const t_btree *root, int depth, int pos,
                      char canvas[100][200], int *max_row)
{
    if (!root) return;

    char *label = get_label(root);
    int col = pos;

    // Write node label
    for (int i = 0; label[i]; i++)
        if (col+i >= 0 && col+i < 200)
            canvas[depth*2][col+i] = label[i];

    if (depth*2 > *max_row)
        *max_row = depth*2;

    int offset = 6 + depth * 2; // spacing grows with depth

    if (root->left)
    {
        if (col-1 >= 0)
            canvas[depth*2+1][col-1] = '/';
        print_ascii_tree(root->left, depth+1, col-offset, canvas, max_row);
    }
    if (root->right)
    {
        int len = strlen(label);
        if (col+len < 200)
            canvas[depth*2+1][col+len] = '\\';
        print_ascii_tree(root->right, depth+1, col+len+offset, canvas, max_row);
    }
}

void print_canvas(char canvas[100][200], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        int end = cols-1;
        while (end >= 0 && canvas[i][end] == ' ')
            end--;
        if (end >= 0)
        {
            for (int j = 0; j <= end; j++)
                putchar(canvas[i][j]);
        }
        putchar('\n');
    }
}

void print_btree_pyramid(const t_btree *root)
{
    char canvas[100][200];
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 200; j++)
            canvas[i][j] = ' ';

    int max_row = 0;
    print_ascii_tree(root, 0, 50, canvas, &max_row);
    print_canvas(canvas, max_row + 2, 200);
}