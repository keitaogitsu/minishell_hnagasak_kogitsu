BUILTIN_DIR := srcs/builtin
BUILTIN_FILES := cd.c echo.c exit.c
BUILTIN_SRCS := $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES))

UTILS_DIR := srcs/utils
UTILS_FILES := list.c
UTILS_SRCS := $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

CC		:= cc
# CFLAGS	:= -Wall -Wextra -Werror
LDLIBS = -lreadline
NAME	:= minishell
RM		:= rm -f
SRCS	:= srcs/main.c srcs/lexer/lexer.c $(BUILTIN_SRCS) $(UTILS_SRCS)
OBJS	:= $(SRCS:.c=.o)
MAKE	:= make
SRCS_DIR	:= srcs
INC_DIR	:= includes
LIBFT_DIR	:= libft
LIBFT_NAME := libft/libft.a
INC := -I$(INC_DIR) -I$(LIBFT_DIR)

%.o: %.c
	$(CC) ${CFLAGS} ${INC} -c $< -o $@

all:	$(NAME)
$(NAME):	$(OBJS)
	$(MAKE) bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INC) $(LIBFT_NAME) $(OBJS) -o $(NAME) $(LDLIBS)

%.o: %.c
	$(CC) ${CFLAGS} ${INC} -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT_NAME) $(NAME)

re:		fclean all

.PHONY: all clean fclean re