
EXEC_DIR := srcs/exec
EXEC_FILES := execmd.c exec_test.c
EXEC_SRCS := $(addprefix $(EXEC_DIR)/, $(EXEC_FILES))

BUILTIN_DIR := srcs/builtin
BUILTIN_FILES := pwd.c cd.c echo.c exit.c env.c export.c unset.c test.c
BUILTIN_SRCS := $(addprefix $(BUILTIN_DIR)/, $(BUILTIN_FILES))

UTILS_DIR := srcs/utils
UTILS_FILES := envp.c free.c list.c t_env.c 
UTILS_SRCS := $(addprefix $(UTILS_DIR)/, $(UTILS_FILES))

LEXER_DIR := srcs/lexer
LEXER_FILES := lexer.c lexer_utils.c token_processing.c quote_process.c validate_token.c validate_token2.c
LEXER_SRCS := $(addprefix $(LEXER_DIR)/, $(LEXER_FILES))

DEBUG_DIR := srcs/debug
DEBUG_FILES := print.c
DEBUG_SRCS := $(addprefix $(DEBUG_DIR)/, $(DEBUG_FILES))

PARSER_DIR := srcs/parser
PARSER_FILES := parser.c parser_utils.c
PARSER_SRCS := $(addprefix $(PARSER_DIR)/, $(PARSER_FILES))

EXPANDER_DIR := srcs/expander
EXPANDER_FILES := expander.c
EXPANDER_SRCS := $(addprefix $(EXPANDER_DIR)/, $(EXPANDER_FILES))

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror
LDLIBS = -lreadline
NAME	:= minishell
RM		:= rm -f
SRCS	:= srcs/main.c $(BUILTIN_SRCS) $(UTILS_SRCS) $(EXEC_SRCS) $(LEXER_SRCS) $(DEBUG_SRCS) $(PARSER_SRCS) $(EXPANDER_SRCS)
OBJS	:= $(SRCS:.c=.o)
MAKE	:= make
SRCS_DIR	:= srcs
INC_DIR	:= includes
LIBFT_DIR	:= libft
LIBFT_NAME := libft/libft.a
RL_DIR = $(shell brew --prefix readline)
INC := -I$(INC_DIR) -I$(LIBFT_DIR) -I$(RL_DIR)/include

%.o: %.c
	$(CC) ${CFLAGS} ${INC} -c $< -o $@

all:	$(NAME)
$(NAME):	$(OBJS)
	$(MAKE) bonus -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(INC) $(LIBFT_NAME) -L$(RL_DIR)/lib $(OBJS) -o $(NAME) $(LDLIBS)
	echo > ~/.inputrc set echo-control-characters off

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT_NAME) $(NAME)

re:		fclean all

.PHONY: all clean fclean re