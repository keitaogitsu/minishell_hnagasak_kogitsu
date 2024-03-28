/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:56:44 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/28 09:41:11 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_single_builtin(t_dlist *current, t_dlist **env_list)
{
	t_cmd	*cmd;
	int		exit_status;

	exit_status = 0;
	cmd = (t_cmd *)current->cont;
	ft_debug("--- exec_single_builtin %s ---\n", cmd->argv[0]);
	set_tmpfile_name(cmd, current->i);
	store_stdio(current);
	input_heredocs(cmd, env_list);
	if (dup_stdin(current) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	if (dup_stdout(current) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	exit_status = exec_builtin(cmd, env_list);
	delete_tmp_files(cmd);
	restore_stdio(current);
	return (exit_status);
}

void	input_heredocuments(t_dlist **cmd_list, t_dlist **env_list)
{
	t_dlist	*current;
	t_cmd	*cmd;

	current = *cmd_list;
	while (current != NULL)
	{
		cmd = (t_cmd *)current->cont;
		store_stdio(current);
		set_tmpfile_name(cmd, current->i);
		input_heredocs(cmd, env_list);
		restore_stdio(current);
		current = current->nxt;
	}
}

int	exec_external_or_piped_cmd(t_dlist **cmd_list, t_dlist **env_list)
{
	t_dlist	*current;
	t_cmd	*cmd;

	current = *cmd_list;
	input_heredocuments(cmd_list, env_list);
	while (current != NULL)
	{
		cmd = (t_cmd *)current->cont;
		ft_debug("\n--- exec_cmd[%d]: %s ---\n", current->i, cmd->argv[0]);
		set_pipe_if_needed(current);
		set_fork(current);
		if (cmd->pid == 0)
			child_process(current, env_list);
		else if (cmd->pid > 0)
			close_parent_pipe(current);
		else
			fail_fork();
		current = current->nxt;
	}
	return (wait_children(cmd_list));
}

void	exec_cmd_list(t_dlist **cmd_list, t_dlist **env_list, int *exit_status)
{
	t_dlist	*current;

	current = *cmd_list;
	if (current == NULL)
		return ;
	if (is_builtin_cmd((t_cmd *)current->cont) && current->nxt == NULL)
		*exit_status = exec_single_builtin(current, env_list);
	else
		*exit_status = exec_external_or_piped_cmd(cmd_list, env_list);
}
