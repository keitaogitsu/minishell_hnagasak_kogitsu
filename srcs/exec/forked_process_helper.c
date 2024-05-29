/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked_process_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:21:39 by hnagasak          #+#    #+#             */
/*   Updated: 2024/05/30 04:19:53 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_parent_pipe(t_dlist *current)
{
	t_cmd	*cmd;
	t_cmd	*prv_cmd;

	cmd = (t_cmd *)current->cont;
	if (current->nxt != NULL)
	{
		ft_debug("[close_parent_pipe] close %d\n", cmd->pipe[1]);
		cmd->pipe[1] = ft_close(cmd->pipe[1]);
	}
	if (current->prv != NULL)
	{
		prv_cmd = (t_cmd *)current->prv->cont;
		ft_debug("[close_parent_pipe] close %d\n", prv_cmd->pipe[0]);
		prv_cmd->pipe[0] = ft_close(prv_cmd->pipe[0]);
	}
}

void	child_process(t_dlist *current, t_dlist **env_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	ft_debug("[child process] close pipin fd:%d\n", cmd->pipe[0]);
	cmd->pipe[0] = ft_close(cmd->pipe[0]);
	store_stdio(current);
	if (dup_stdin(current) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (dup_stdout(current) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	exec_cmd(cmd, env_list);
}

void	fail_fork(t_dlist *current)
{
	t_dlist	*prev;
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	perror("fork");
	cmd->pipe[0] = ft_close(cmd->pipe[0]);
	cmd->pipe[1] = ft_close(cmd->pipe[1]);
	prev = current->prv;
	if (prev != NULL)
	{
		cmd = (t_cmd *)prev->cont;
		cmd->pipe[0] = ft_close(cmd->pipe[0]);
	}
}

// wait for all child processes to finish
int	wait_children(t_dlist **cmd_list)
{
	t_dlist	*current;
	t_cmd	*cmd;
	int		status;

	current = *cmd_list;
	while (current != NULL)
	{
		cmd = (t_cmd *)current->cont;
		waitpid(cmd->pid, &status, 0);
		ft_debug("[waitpid] %d: %d.%s\n", cmd->pid, current->i, cmd->argv[0]);
		delete_tmp_files(cmd);
		current = current->nxt;
	}
	return (status % 255);
}
