/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:51:26 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/28 22:27:34 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// tokenがCHAR_GENERALかどうかを判定する
int	has_string(t_token *tkn_list)
{
	if (tkn_list == NULL)
		return (0);
	if (tkn_list->type == CHAR_GENERAL || tkn_list->type == CHAR_QUOTE
		|| tkn_list->type == CHAR_DQUOTE)
		return (1);
	else
		return (0);
}

// tokenがCHAR_GENERALかつ次のtokenがないことを判定する
int	is_string(t_token *tkn_list)
{
	if (tkn_list == NULL)
		return (0);
	if (has_string(tkn_list) && tkn_list->next == NULL)
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

// 先頭2つのtokenがredir_signとstringであることを判定する
int	has_redirection(t_token *tkn_list)
{
	if (tkn_list == NULL || tkn_list->next == NULL)
		return (0);
	if (is_redir_sign(tkn_list) && has_string(tkn_list->next))
		return (1);
	else
		return (0);
}

// 先頭2つのtokenがredir_signとstringかつ、それ以降にtokenがないことを判定する
int	is_redirection(t_token *tkn_list)
{
	if (tkn_list == NULL || tkn_list->next == NULL)
		return (0);
	if (has_redirection(tkn_list) && tkn_list->next->next == NULL)
		return (1);
	else
		return (0);
}
