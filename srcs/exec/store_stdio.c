/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_stdio.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:49:52 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/07 01:50:38 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// 標準入出力を保存しておく
void	store_stdio(t_dlist *current)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	cmd->stdio[0] = dup(STDIN_FILENO);
	cmd->stdio[1] = dup(STDOUT_FILENO);
	if (cmd->stdio[0] == -1 || cmd->stdio[1] == -1)
	{
		perror("[store_stdio] dup error");
		ft_debug("[store_stdio] stdio(%d,%d)\n", cmd->stdio[0], cmd->stdio[1]);
		cmd->stdio[0] = ft_close(cmd->stdio[0]);
		cmd->stdio[1] = ft_close(cmd->stdio[1]);
	}
	else
		ft_debug("[store_stdio] stdio(%d,%d)\n", cmd->stdio[0], cmd->stdio[1]);
}

void	restore_stdio(t_dlist *current)
{
	t_cmd	*cmd;
	int		res[2];

	cmd = (t_cmd *)current->cont;
	ft_debug("[restore_stdio] (%d,%d)\n", cmd->stdio[0], cmd->stdio[1]);
	res[0] = dup2(cmd->stdio[0], STDIN_FILENO);
	res[1] = dup2(cmd->stdio[1], STDOUT_FILENO);
	if (res[0] != -1 && res[1] != -1)
	{
		cmd->stdio[0] = ft_close(cmd->stdio[0]);
		cmd->stdio[1] = ft_close(cmd->stdio[1]);
	}
}
