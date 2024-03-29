# - * - Makefile - * -

SRC_LIB = ft_split.c ft_split2.c ft_strnstr.c ft_strlen.c\
		ft_strjoin.c ft_strtrim.c ft_strchr.c ft_strlcpy.c ft_putstr_fd.c

SRC_PRT = ft_printf.c  ft_check.c ft_puthexa.c utils.c

SRC_PPX = pipex.c utils.c

SRC_BNS = pipex_bonus.c utils_bonus.c

SRCS = $(addprefix mandatory/, $(SRC_PPX)) $(addprefix libft/, $(SRC_LIB))\
		$(addprefix ft_printf/, $(SRC_PRT))

SRCS_B = $(addprefix bonus/, $(SRC_BNS)) $(addprefix libft/, $(SRC_LIB))\
		$(addprefix ft_printf/, $(SRC_PRT))

OBJS = $(SRCS:%.c=%.o)
OBJS_B = $(SRCS_B:%.c=%.o)
NAME = pipex
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "\033[0;32mCompiled!\033[0m"

bonus: $(OBJS_B)
		@$(CC) $(CFLAGS) $(OBJS_B) -o $(NAME)
		@echo "\033[0;32mCompiled!\033[0m"

clean:
		@$(RM) $(OBJS) $(OBJS_B)

fclean: clean
		@$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re run val