/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:21:27 by kogitsu           #+#    #+#             */
/*   Updated: 2024/05/24 20:45:56 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "lexer.h"
#include "utils.h"

int	is_arguments(t_token *tkn_list)
{
	if (tkn_list == NULL)
		return (0);
	if (tkn_list->type == CHAR_PIPE && tkn_list->next != NULL
		&& tkn_list->next->type != CHAR_PIPE)
		return (is_arguments(tkn_list->next));
	if (is_redirection(tkn_list))
		return (1);
	else if (has_redirection(tkn_list) && is_arguments(tkn_list->next->next))
		return (1);
	else if (has_string(tkn_list) && tkn_list->next != NULL
		&& is_arguments(tkn_list->next))
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

int	is_pipe(t_token *tkn_list)
{
	if (tkn_list->type == CHAR_PIPE)
		return (1);
	else
		return (0);
}

int	is_piped_commands(t_token *tkn_list)
{
	if (is_command(tkn_list))
		return (1);
	else if (is_command(tkn_list) && is_pipe(tkn_list->next)
		&& is_piped_commands(tkn_list->next->next))
		return (1);
	return (0);
}

// "\n"
// | sequencial_commands delimiter "\n"
// | sequencial_commands "\n"
int	is_cmd_line(t_token *tkn_list)
{
	if (tkn_list == NULL)
		return (0);
	if (is_piped_commands(tkn_list))
		return (1);
	else
	{
		free_tokens(tkn_list);
		ft_errmsg("minishell: syntax error\n");
		return (0);
	}
}
