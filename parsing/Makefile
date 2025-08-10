NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft -g
LIBS = -lreadline -lhistory
HEADERS = minishell.h libft/libft.h
LIBFT = libft/libft.a

SRC = main.c parse.c

DIR_OBJ = objects/

OBJ = $(SRC:%.c=$(DIR_OBJ)%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(LIBS) $(OBJ) $(LIBFT) -o $(NAME)

$(DIR_OBJ)%.o: %.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_OBJ):
	mkdir -p $@

############### LIBFT ###############
$(LIBFT):
	make -C libft
############### LIBFT ###############

clean:
	rm -rf $(DIR_OBJ)
	make clean -C libft

fclean:
	rm -rf $(DIR_OBJ) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re