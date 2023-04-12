# - * - Makefile - * -

PRT_SRC = ft_printf/ft_printf.c  ft_printf/ft_check.c ft_printf/ft_puthexa.c\
		ft_printf/utils.c

SRC_LIB = libft/ft_split.c libft/ft_split2.c libft/ft_substr.c libft/ft_strnstr.c\
		libft/ft_strlen.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_strrchr.c\
		libft/ft_strchr.c libft/ft_strlcpy.c libft/ft_putstr_fd.c

SRCS = main.c utils.c $(SRC_LIB) $(PRT_SRC)

OBJS = $(SRCS:.c=.o)
NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -rf

all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -I . $< -o $@

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

run: $(NAME)
		@./pipex aa "ls -l" "cat" bb

val: $(NAME)
		valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --trace-children=yes ./pipex aa "asda" "dsasdasda" bb

clean:
		@$(RM) $(OBJS)

fclean: clean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re run val