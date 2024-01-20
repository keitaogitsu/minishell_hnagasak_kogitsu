/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:51:26 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/20 16:01:46 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	is_string(t_token *tkn_list)
{
	if (tkn_list->type == CHAR_GENERAL)
		return (1);
	else
		return (0);
}

int	is_pipe(t_token *tkn_list)
{
	if (tkn_list->type == CHAR_PIPE)
		return (1);
	else
		return (0);
}

int	is_redir_sign(t_token *tkn_list)
{
	if (tkn_list->type == CHAR_GREATER || tkn_list->type == CHAR_LESSER
		|| tkn_list->type == D_GREATER || tkn_list->type == D_LESSER)
		return (1);
	else
		return (0);
}

int	is_redirection(t_token *tkn_list)
{
	if (is_redir_sign(tkn_list) && is_string(tkn_list->next))
		return (1);
	else
		return (0);
}

// arguments ::=
//       redirection
//     | redirection arguments
//     | string
//     | string arguments
int	is_arguments(t_token *tkn_list)
{
	if (is_redirection(tkn_list))
		return (1);
	else if (is_redirection(tkn_list) && is_arguments(tkn_list->next))
		return (1);
	else if (is_string(tkn_list) && is_arguments(tkn_list->next))
		return (1);
	else if (is_string(tkn_list))
		return (1);
	else
		return (0);
}

int	is_command(t_token *tkn_list)
{
	if (is_arguments(tkn_list))
		return (1);
	else
		return (0);
}

int	is_piped_commands(t_token *tkn_list)
{
	if (is_command(tkn_list))
		return (1);
	if (is_command(tkn_list) && is_pipe(tkn_list->next)
		&& is_piped_commands(tkn_list->next->next))
		return (1);
	else
		return (0);
}

// "\n"
// | sequencial_commands delimiter "\n"
// | sequencial_commands "\n"
int	is_cmd_line(t_token *tkn_list)
{
	if (is_piped_commands(tkn_list))
		return (1);
	else
		return (0);
}
