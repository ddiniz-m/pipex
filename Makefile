# - * - Makefile - * -

PRT_SRC = ft_printf/ft_printf.c  ft_printf/ft_check.c ft_printf/ft_puthexa.c\
		ft_printf/utils.c

SRC_LIB = libft/ft_split.c libft/ft_substr.c libft/ft_strnstr.c\
		libft/ft_strlen.c libft/ft_strjoin.c

SRCS = main.c $(SRC_LIB) $(PRT_SRC)

OBJS = $(SRCS:%.c=%.o)
NAME = pipex
CC = @gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) -g $(SRCS) -o $(NAME)

run: $(NAME)
		@./pipex

val: $(NAME)
		@valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

clean:
		@$(RM) $(OBJS)

fclean: clean
		@$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re run val