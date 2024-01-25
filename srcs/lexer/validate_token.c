/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:51:26 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/25 20:04:03 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// // 渡したtokenがCHAR_GENERALかどうかを判定する
// int	is_char_general(t_token *tkn_list)
// {
// 	printf("=== is_char_general (%s)=== ", tkn_list->str);
// 	if (tkn_list->type == CHAR_GENERAL)
// 		return (1);
// 	else
// 		return (0);
// }

// tokenがCHAR_GENERALかどうかを判定する
int	has_string(t_token *tkn_list)
{
	if (tkn_list == NULL)
		return (0);
	printf("=== has_string (%s)=== ", tkn_list->str);
	if (tkn_list->type == CHAR_GENERAL)
	{
		printf("True\n");
		return (1);
	}
	else
	{
		printf("False\n");
		return (0);
	}
}

// tokenがCHAR_GENERALかつ次のtokenがないことを判定する
int	is_string(t_token *tkn_list)
{
	if (tkn_list == NULL)
		return (0);
	printf("=== is_string (%s)=== ", tkn_list->str);
	if (has_string(tkn_list) && tkn_list->next == NULL)
	{
		printf("True\n");
		return (1);
	}
	else
	{
		printf("False\n");
		return (0);
	}
}

int	is_pipe(t_token *tkn_list)
{
	printf("--- is_pipe (%s)--- ", tkn_list->str);
	if (tkn_list->type == CHAR_PIPE)
	{
		printf("True\n");
		return (1);
	}
	else
	{
		printf("False\n");
		return (0);
	}
}

int	is_redir_sign(t_token *tkn_list)
{
	printf("--- is_redir_sign (%s)--- ", tkn_list->str);
	if (tkn_list->type == CHAR_GREATER || tkn_list->type == CHAR_LESSER
		|| tkn_list->type == D_GREATER || tkn_list->type == D_LESSER)
	{
		printf("True\n");
		return (1);
	}
	else
	{
		printf("False\n");
		return (0);
	}
}

// 先頭2つのtokenがredir_signとstringであることを判定する
int	has_redirection(t_token *tkn_list)
{
	printf("=== has_redirection (%s)===\n", tkn_list->str);
	if (tkn_list == NULL || tkn_list->next == NULL)
		return (0);
	if (is_redir_sign(tkn_list) && is_string(tkn_list->next))
	{
		printf("--- is_redirection (%s)--- True\n", tkn_list->str);
		return (1);
	}
	else
	{
		printf("--- is_redirection (%s)--- False\n", tkn_list->str);
		return (0);
	}
}

// 先頭2つのtokenがredir_signとstringかつ、それ以降にtokenがないことを判定する
int	is_redirection(t_token *tkn_list)
{
	if (tkn_list == NULL || tkn_list->next == NULL)
		return (0);
	printf("=== is_redirection (%s)===\n", tkn_list->str);
	if (has_redirection(tkn_list) && tkn_list->next->next == NULL)
	{
		printf("--- is_redirection (%s)--- True\n", tkn_list->str);
		return (1);
	}
	else
	{
		printf("--- is_redirection (%s)--- False\n", tkn_list->str);
		return (0);
	}
}

// arguments ::=
//       redirection
//     | redirection arguments
//     | string
//     | string arguments
int	is_arguments(t_token *tkn_list)
{
	printf("=== is_arguments (%s)===\n", tkn_list->str);
	if (is_redirection(tkn_list) && tkn_list->next->next == NULL)
	{
		printf("--- is_arguments (%s)---1 True\n", tkn_list->str);
		return (1);
	}
	else if (has_redirection(tkn_list) && is_arguments(tkn_list->next->next))
	{
		printf("--- is_arguments (%s)---2 True\n", tkn_list->str);
		return (1);
	}
	else if (has_string(tkn_list) && tkn_list->next != NULL
		&& is_arguments(tkn_list->next))
	{
		printf("--- is_arguments (%s)---3 True\n", tkn_list->str);
		return (1);
	}
	else if (is_string(tkn_list))
	{
		printf("--- is_arguments (%s)---4 True\n", tkn_list->str);
		return (1);
	}
	else
	{
		printf("--- is_arguments (%s)--- False\n", tkn_list->str);
		return (0);
	}
}

int	is_command(t_token *tkn_list)
{
	printf("=== is_command (%s)===\n", tkn_list->str);
	if (is_arguments(tkn_list))
	{
		printf("--- is_command (%s)--- True\n", tkn_list->str);
		return (1);
	}
	else
	{
		printf("--- is_command (%s)--- False\n", tkn_list->str);
		return (0);
	}
}

int	is_piped_commands(t_token *tkn_list)
{
	printf("=== is_piped_commands (%s)===\n", tkn_list->str);
	if (is_command(tkn_list))
	{
		printf("--- is_piped_commands (%s)---1 True\n\n", tkn_list->str);
		return (1);
	}
	else if (is_command(tkn_list) && is_pipe(tkn_list->next)
		&& is_piped_commands(tkn_list->next->next))
	{
		printf("--- is_piped_commands (%s)---2 True\n\n", tkn_list->str);
		return (1);
	}
	else
		printf("--- is_piped_commands (%s)--- False\n\n", tkn_list->str);
	return (0);
}

// "\n"
// | sequencial_commands delimiter "\n"
// | sequencial_commands "\n"
int	is_cmd_line(t_token *tkn_list)
{
	printf("--- is_cmd_line (%s)---\n", tkn_list->str);
	if (is_piped_commands(tkn_list))
		return (1);
	else
		return (0);
}
