/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 12:25:53 by kogitsu           #+#    #+#             */
/*   Updated: 2024/02/17 12:26:52 by kogitsu          ###   ########.fr       */
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

t_redir	*crt_redir(char *file, t_redir_type type)
{
    t_redir	*redir;

    redir = malloc(sizeof(t_redir));
    if (redir == NULL)
        return (NULL);
    redir->file = file;
    redir->type = type;
    return (redir);
}

t_cmd	*cmd_init(t_token *tokens, t_dlist **env_list)
{
    t_cmd	*cmd;

    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (cmd == NULL)
        return (NULL);
    cmd->argv = (char **)malloc(sizeof(char *) * (get_argv_len(tokens) + 1));
    if (cmd->argv == NULL)
        return (NULL);
    cmd->envp = env_list;
    cmd->stdio[0] = -1;
    cmd->stdio[1] = -1;
    cmd->pipe[0] = -1;
    cmd->pipe[1] = -1;
    return (cmd);
}

void	cmd_output_join(t_cmd *cmd, t_redir *redir)
{
	if (cmd->output == NULL)
		cmd->output = ft_dlstnew(redir);
	else
		ft_dlstadd_back(&cmd->output, ft_dlstnew(redir));
}