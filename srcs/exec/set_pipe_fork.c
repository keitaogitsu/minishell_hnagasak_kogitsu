/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:09:50 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/22 06:15:39 by hnagasak         ###   ########.fr       */
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

// 子プロセスを作成する
// old:外部コマンドまたは次のコマンドがある場合、子プロセスを作成する
void	set_fork(t_dlist *current)
{
	t_cmd	*cmd;

	ft_debug("--- set_fork ---\n");
	cmd = (t_cmd *)current->cont;
	cmd->pid = fork();
}
