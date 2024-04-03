/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 21:14:05 by kogitsu           #+#    #+#             */
/*   Updated: 2024/04/04 04:36:34 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
// Error if included before stdio.h
# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_token_type
{
	CHAR_GENERAL = -1,
	CHAR_PIPE = '|',
	CHAR_QUOTE = '\'',
	CHAR_DQUOTE = '\"',
	CHAR_WHITESPACE = ' ',
	CHAR_ESCAPE = '\\',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_TAB = '\t',
	CHAR_NULL = 0,
	D_GREATER = -3,
	D_LESSER = -2,
}					t_token_type;

typedef enum e_token_state
{
	STATE_IN_DQUOTE,
	STATE_IN_QUOTE,
	STATE_GENERAL,
}					t_token_state;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_tokenizer
{
	size_t			line_i;
	size_t			token_str_i;
	size_t			str_len;
	t_token			*tmp_token;
	t_token			*tokens_head;
	t_token_state	state;
}					t_tokenizer;

t_token				*tokenize(char *line);
t_token_type		get_type(char c);
void				general_state_process(t_tokenizer *toker, char *line,
						t_token_type type);
t_token				*token_init(size_t len);
void				print_tokenizer(t_tokenizer *tokenizer);
void				quote_state_process(t_tokenizer *toker, char *line,
						t_token_type type);
void				dquote_state_process(t_tokenizer *toker, char *line,
						t_token_type type);
void				complete_current_token(t_tokenizer *toker,
						t_token_type type);

// validate_token.c validate_token2.c
int					is_cmd_line(t_token *tkn_list);
int					is_piped_commands(t_token *tkn_list);
int					is_pipe(t_token *tkn_list);
int					is_command(t_token *tkn_list);
int					is_arguments(t_token *tkn_list);
int					is_redirection(t_token *tkn_list);
int					has_redirection(t_token *tkn_list);
int					is_redir_sign(t_token *tkn_list);
int					is_string(t_token *tkn_list);
int					has_string(t_token *tkn_list);

#endif