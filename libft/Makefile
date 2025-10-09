NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRC = ft_append_arr_str.c ft_arrlen.c ft_atoi.c ft_calloc.c ft_copyarr.c \
		ft_free_arr.c ft_free_split.c ft_get_env_value.c ft_isalnum.c ft_isalpha.c ft_isdigit.c \
		ft_printf.c ft_printf_utils.c ft_putstr_fd.c ft_putstrerr.c ft_split_dels.c \
		ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strjoinf1.c ft_strlcpy.c \
		ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strsjoin.c ft_substr.c \
		ft_write_types.c ft_write_types2.c

OBJ_DIR = objects/

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re