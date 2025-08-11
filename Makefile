NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
PIPEX = binary_path.c\
		here_doc.c\
		main_bonus.c\
		piping_the_child.c\
		pipex_utils.c
EXECFILES = haha.c
COMMANDS = commands/cd.c\
		   commands/com_main.c\
		   commands/pwd.c\
		   commands/env.c\
		   commands/unset.c\
		   commands/export.c
LIBFT = libft/ft_calloc.c\
		libft/ft_putstr_fd.c\
		libft/ft_split.c\
		libft/ft_strchr.c\
		libft/ft_strdup.c\
		libft/ft_strlen.c\
		libft/ft_strncmp.c\
		libft/ft_strnstr.c\
		libft/ft_substr.c\
		libft/ft_isalnum.c\
		libft/ft_isalpha.c\
		libft/ft_digit.c
STAR = star/test.c
FILES = $(EXECFILES)
OBJ = $(FILES:.c=.o)


all : $(OBJ) $(NAME)
	

$(NAME): $(OBJ)
	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)


%.o : %.c libft.h
	$(CC) $(CFLAGS) -c   $< -o $@
	
clean :
	rm -f $(OBJ) $(BOBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all


exec:
	cc -Wall -Wextra $(EXECFILES) -g -o exec
	
com:
	cc -Wall -Wextra $(COMMANDS) libft/*.c -g -o com

star:
	cc -Wall -Wextra $(STAR) libft/*.c -g -o sta

.PHONY: re fclean clean all com star
