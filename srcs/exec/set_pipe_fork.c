/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:09:50 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/07 02:10:26 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// 次のコマンドが存在する場合、pipeを作成する
void	set_pipe_if_needed(t_dlist *current)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	if (current->nxt != NULL)
		ft_pipe(cmd->pipe);
	else
		ft_debug("[set_pipe] unset pipe\n");
}

// 外部コマンドまたは次のコマンドがある場合、子プロセスを作成する
void	set_fork_if_needed(t_dlist *current)
{
	t_cmd	*cmd;

	ft_debug("--- set_fork_if_needed ---\n");
	cmd = (t_cmd *)current->cont;
	if (!is_builtin_cmd(cmd) || current->nxt != NULL)
	{
		ft_debug("  should fork\n");
		cmd->pid = fork();
	}
	else
		ft_debug("  No fork\n");
}
