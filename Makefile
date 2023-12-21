CC		:= cc
# CFLAGS	:= -Wall -Wextra -Werror
LDLIBS = -lreadline
NAME	:= minishell
RM		:= rm -f
SRCS	:= srcs/main.c srcs/lexer/lexer.c
OBJS	:= $(SRCS:.c=.o)
MAKE	:= make
SRCS_DIR	:= srcs
INC_DIR	:= includes
LIBFT_DIR	:= libft
LIBFT_NAME := libft/libft.a
INC := -I$(INC_DIR) -I$(LIBFT_DIR)


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