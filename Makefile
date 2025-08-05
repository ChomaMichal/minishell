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
		   commands/pwd.c
LIBFT = libft/ft_calloc.c\
		libft/ft_putstr_fd.c\
		libft/ft_split.c\
		libft/ft_strchr.c\
		libft/ft_strdup.c\
		libft/ft_strlen.c\
		libft/ft_strncmp.c\
		libft/ft_strnstr.c\
		libft/ft_substr.c
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
	cc -Wall -Wextra $(COMMANDS) -g -o com

.PHONY: re fclean clean all com
