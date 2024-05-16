/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:56:44 by hnagasak          #+#    #+#             */
/*   Updated: 2024/05/16 20:08:34 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_handlers.h"

int	exec_single_builtin(t_dlist *current, t_dlist **env_list, int exit_status)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	ft_debug("--- exec_single_builtin %s ---\n", cmd->argv[0]);
	set_tmpfile_name(cmd, current->i);
	store_stdio(current);
	input_heredocs(cmd, env_list, exit_status);
	if (dup_stdin(current) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (dup_stdout(current) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	signal(SIGINT, sigint_handler_in_exec);
	signal(SIGQUIT, sigquit_handler_in_exec);
	exit_status = exec_builtin(cmd, env_list);
	delete_tmp_files(cmd);
	restore_stdio(current);
	return (exit_status);
}

void	input_heredocuments(t_dlist **cmd_list, t_dlist **env_list,
		int exit_status)
{
	t_dlist	*current;
	t_cmd	*cmd;

	current = *cmd_list;
	while (current != NULL)
	{
		cmd = (t_cmd *)current->cont;
		store_stdio(current);
		set_tmpfile_name(cmd, current->i);
		input_heredocs(cmd, env_list, exit_status);
		restore_stdio(current);
		current = current->nxt;
	}
}

int	exec_external_or_piped_cmd(t_dlist **cmd_list, t_dlist **env_list,
		int exit_status)
{
	t_dlist	*current;
	t_cmd	*cmd;

	current = *cmd_list;
	ft_debug("--- exec_external_or_piped_cmd ---\n");
	input_heredocuments(cmd_list, env_list, exit_status);
	signal(SIGINT, sigint_handler_in_exec);
	signal(SIGQUIT, sigquit_handler_in_exec);
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
		*exit_status = exec_single_builtin(current, env_list, *exit_status);
	else
		*exit_status = exec_external_or_piped_cmd(cmd_list, env_list,
				*exit_status);
}
