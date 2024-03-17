/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked_process_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:21:39 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/17 19:54:01 by hnagasak         ###   ########.fr       */
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
	input_heredocs(cmd, env_list);
	dup_stdin(current);
	dup_stdout(current);
	exec_cmd(cmd, env_list);
}

void	fail_fork(void)
{
	perror("fork");
	exit(EXIT_FAILURE);
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
