/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:20:30 by kogitsu           #+#    #+#             */
/*   Updated: 2024/02/28 00:52:55 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	process_redir(t_token **tokens, t_cmd *cmd, t_redir_type redir_type)
{
	t_redir	*redir;

	*tokens = (*tokens)->next;
	redir = crt_redir((*tokens)->str, redir_type);
	if (redir_type == REDIR_INPUT || redir_type == REDIR_HEREDOC)
		ft_dlstadd_back(&cmd->input, ft_dlstnew(redir));
	else if (redir_type == REDIR_OUTPUT || redir_type == REDIR_APPEND)
		ft_dlstadd_back(&cmd->output, ft_dlstnew(redir));
}

void	create_cmd(t_token **tokens, t_cmd *cmd, size_t *i)
{
	t_token	*token;

	token = *tokens;
	if (token->type == CHAR_GENERAL || token->type == CHAR_QUOTE
		|| token->type == CHAR_DQUOTE)
	{
		cmd->argv[*i] = ft_strdup(token->str);
		*i = *i + 1;
	}
	else if (token->type == CHAR_GREATER)
		process_redir(tokens, cmd, REDIR_OUTPUT);
	else if (token->type == CHAR_LESSER)
		process_redir(tokens, cmd, REDIR_INPUT);
	else if (token->type == D_GREATER)
		process_redir(tokens, cmd, REDIR_APPEND);
	else if (token->type == D_LESSER)
		process_redir(tokens, cmd, REDIR_HEREDOC);
}

t_dlist	**create_cmd_list(t_token *tokens, t_dlist **env_list)
{
	t_dlist	**cmd_list;
	t_cmd	*cmd;
	size_t	i;

	cmd_list = (t_dlist **)malloc(sizeof(t_dlist *));
	while (tokens != NULL)
	{
		i = 0;
		cmd = cmd_init(tokens, env_list);
		while (tokens != NULL && tokens->type != CHAR_PIPE)
		{
			create_cmd(&tokens, cmd, &i);
			tokens = tokens->next;
		}
		if (*cmd_list == NULL)
			*cmd_list = ft_dlstnew(cmd);
		else
			ft_dlstadd_back(cmd_list, ft_dlstnew(cmd));
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (cmd_list);
}
