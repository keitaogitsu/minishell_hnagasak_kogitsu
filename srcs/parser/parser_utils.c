/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:25:53 by kogitsu           #+#    #+#             */
/*   Updated: 2024/03/21 20:55:12 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	get_argv_len(t_token *token)
{
	size_t	len;

	len = 0;
	while (token != NULL && token->type != CHAR_PIPE)
	{
		len++;
		token = token->next;
	}
	return (len);
}

t_redir	*crt_redir(char *str, t_redir_type type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (redir == NULL)
		malloc_error_exit();
	redir->type = type;
	if (type == REDIR_HEREDOC)
		redir->delimiter = ft_strdup(str);
	else
		redir->file = ft_strdup(str);
	return (redir);
}

t_cmd	*cmd_init(t_token *tokens, t_dlist **env_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		malloc_error_exit();
	cmd->argv = (char **)malloc(sizeof(char *) * (get_argv_len(tokens) + 1));
	if (cmd->argv == NULL)
		malloc_error_exit();
	*(cmd->argv) = NULL;
	cmd->envp = env_list;
	cmd->path = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	cmd->stdio[0] = -1;
	cmd->stdio[1] = -1;
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	cmd->pid = 0;
	return (cmd);
}

// void cmd_output_join(t_cmd *cmd, t_redir *redir)
// {
//      if (cmd->output == NULL)
//              cmd->output = ft_dlstnew(redir);
//      else
//              ft_dlstadd_back(&cmd->output, ft_dlstnew(redir));
// }%