NAME = minishell
CC = cc
CFLAGS = -g
LIBS = -lreadline -lhistory
HEADERS = minishell.h libft/libft.h parsing/parsing.h commands/commands.h ids/ids.h execution/execution.h

SRC = main.c btree_apply.c print.c \
		parsing/execution_tree.c parsing/fragment.c parsing/parsing.c parsing/tokenize.c parsing/validate_tokens.c \
		parsing/ft_lstadd_back.c parsing/ft_lstclear.c parsing/ft_lstdelone.c parsing/ft_lstiter.c parsing/ft_lstlast.c \
		parsing/ft_lstnew.c parsing/parsing_utils.c parsing/tokenize_utils.c \
		commands/cd.c commands/com_main.c commands/echo.c commands/env.c commands/export.c commands/pwd.c commands/unset.c commands/set_rt.c \
		libft/ft_append_arr_str.c libft/ft_arrlen.c libft/ft_atoi.c libft/ft_calloc.c libft/ft_copyarr.c \
		libft/ft_free_arr.c libft/ft_free_split.c libft/ft_get_env_value.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isdigit.c \
		libft/ft_printf.c libft/ft_printf_utils.c libft/ft_putstr_fd.c libft/ft_putstrerr.c libft/ft_split_dels.c \
		libft/ft_split.c libft/ft_strchr.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strjoinf1.c libft/ft_strlcpy.c \
		libft/ft_strlen.c libft/ft_strncmp.c libft/ft_strnstr.c libft/ft_strsjoin.c libft/ft_substr.c \
		libft/ft_write_types.c libft/ft_write_types2.c
		# execution/binsearch.c execution/entry.c execution/execution_utils.c execution/ft_and.c execution/ft_command.c execution/ft_or.c execution/ft_pipe.c

OBJ_DIR = objects/
PARSING_OBJ_DIR = objects/parsing/
COMMANDS_OBJ_DIR = objects/commands/
EXECUTION_OBJ_DIR = objects/execution/
LIBFT_OBJ_DIR = objects/libft/

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $(NAME)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR) $(PARSING_OBJ_DIR) $(COMMANDS_OBJ_DIR) $(EXECUTION_OBJ_DIR) $(LIBFT_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(PARSING_OBJ_DIR):
	mkdir -p $@

$(COMMANDS_OBJ_DIR):
	mkdir -p $@

$(EXECUTION_OBJ_DIR):
	mkdir -p $@

$(LIBFT_OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR):
	mkdir -p $@

test: all
	valgrind --leak-check=full --suppressions=readline.supp ./minishell

ctest: all
	./minishell

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(MINISHELL)

re: fclean all

.PHONY: all clean fclean re