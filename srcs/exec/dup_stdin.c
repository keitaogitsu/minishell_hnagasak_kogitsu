/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_stdin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:43:16 by hnagasak          #+#    #+#             */
/*   Updated: 2024/05/30 04:12:26 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// リダイレクトやパイプに応じて標準入力を書き換える
int	dup_stdin(t_dlist *current)
{
	t_cmd	*cmd;
	int		fd;

	cmd = (t_cmd *)current->cont;
	if (current->prv == NULL && cmd->input == NULL)
		ft_debug("[dup_stdin]  %s: Not dup stdin\n", cmd->argv[0]);
	else if (current->prv == NULL && cmd->input != NULL)
	{
		fd = get_dupin_fd(cmd);
		if (fd == -1)
			return (EXIT_FAILURE);
		dup2(fd, STDIN_FILENO);
		fd = ft_close(fd);
	}
	else if (current->prv != NULL && cmd->input == NULL)
		pipout2stdin(current->prv);
	else if (current->prv != NULL && cmd->input != NULL)
	{
		fd = get_dupin_fd(cmd);
		if (fd == -1)
			return (EXIT_FAILURE);
		dup2(fd, STDIN_FILENO);
		fd = ft_close(fd);
	}
	return (EXIT_SUCCESS);
}

// 指定したコマンドの最後の入力リダイレクションのfdを返す。
int	get_dupin_fd(t_cmd *cmd)
{
	t_dlist	*last;
	t_redir	*rdr;
	int		fd;

	last = cmd->input;
	while (last->nxt != NULL)
	{
		rdr = (t_redir *)last->cont;
		if (rdr->type == REDIR_INPUT || rdr->type == REDIR_HEREDOC)
		{
			fd = file_open(rdr->file, O_RDONLY, 0);
			if (fd == -1)
				return (fd);
			fd = ft_close(fd);
		}
		last = last->nxt;
	}
	rdr = (t_redir *)last->cont;
	if (rdr->type == REDIR_INPUT || rdr->type == REDIR_HEREDOC)
		return (file_open(rdr->file, O_RDONLY, 0));
	else
		ft_errmsg("error: invalid input redir type\n");
	exit(EXIT_FAILURE);
}

// 前コマンドのパイプ出力を標準入力にする
void	pipout2stdin(t_dlist *cmdlst)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmdlst->cont;
	dup2(cmd->pipe[0], STDIN_FILENO);
	ft_close(cmd->pipe[0]);
}
