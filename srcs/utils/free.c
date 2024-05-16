/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 21:53:13 by kogitsu           #+#    #+#             */
/*   Updated: 2024/05/16 20:23:31 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_redir(t_dlist *redir_list)
{
	t_redir	*redir;
	t_dlist	*tmp;

	while (redir_list != NULL)
	{
		tmp = redir_list;
		redir = (t_redir *)redir_list->cont;
		free(redir->file);
		redir->file = NULL;
		if (redir->type == REDIR_HEREDOC)
		{
			free(redir->delimiter);
			redir->delimiter = NULL;
		}
		free(redir);
		redir_list->cont = NULL;
		redir_list = redir_list->nxt;
		free(tmp);
		tmp = NULL;
	}
}

void	*ft_free(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	return (NULL);
}

void	free_cmd(t_cmd *cmd)
{
	size_t	argc;
	size_t	i;

	argc = get_argc(cmd->argv);
	i = 0;
	while (i < argc)
	{
		cmd->argv[i] = ft_free(cmd->argv[i]);
		i++;
	}
	cmd->argv = ft_free(cmd->argv);
	cmd->path = ft_free(cmd->path);
	free_redir(cmd->input);
	free_redir(cmd->output);
	cmd = ft_free(cmd);
}

void	free_cmd_list(t_dlist **cmd_list)
{
	t_dlist	*tmp;
	t_dlist	*current;
	t_cmd	*cmd;

	current = *cmd_list;
	while (current != NULL)
	{
		tmp = current;
		cmd = (t_cmd *)tmp->cont;
		free_cmd(cmd);
		current = current->nxt;
		tmp = ft_free(tmp);
	}
	free(cmd_list);
}
