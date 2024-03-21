/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_stdout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:45:53 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/21 16:48:44 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

void	dup_stdout(t_dlist *current)
{
	t_cmd	*cmd;
	int		fd;

	cmd = (t_cmd *)current->cont;
	if (current->nxt == NULL && cmd->output == NULL)
	{
		ft_debug("[dup_stdout] %s: Not dup stdout\n", cmd->argv[0]);
	}
	else if (current->nxt == NULL && cmd->output != NULL)
	{
		fd = get_dupout_fd(cmd);
		dup2(fd, STDOUT_FILENO);
		ft_debug("[dup_stdout] %s: dup output redir (%d)\n", cmd->argv[0], fd);
	}
	else if (current->nxt != NULL && cmd->output == NULL)
	{
		pipin2stdout(current);
		ft_debug("[dup_stdout] %s: dup pipin2stdout\n", cmd->argv[0]);
	}
	else if (current->nxt != NULL && cmd->output != NULL)
	{
		fd = get_dupout_fd(cmd);
		dup2(fd, STDOUT_FILENO);
		ft_debug("[dup_stdout] %s: dup output redir (%d)\n", cmd->argv[0], fd);
	}
}

// コマンドの最後の出力リダイレクションに対応するファイルを開き、そのファイルディスクリプタを返す。
// リダイレクションのタイプに応じて、ファイルを上書きまたは追記モードで開く。
int	get_dupout_fd(t_cmd *cmd)
{
	t_dlist	*last;
	t_redir	*rdr;

	last = cmd->output;
	while (last->nxt != NULL)
	{
		// 途中のリダイレクションもファイルは作成する
		rdr = (t_redir *)last->cont;
		file_open(rdr->file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
		last = last->nxt;
	}
	rdr = (t_redir *)last->cont;
	// if(is_updatable_file(rdr->file))
	// {
	// 	ft_errmsg("minishell: ");
	// 	ft_errmsg(rdr->file);
	// 	ft_errmsg(": Is a directory!!\n");
	// 	exit(EXIT_FAILURE);
	// }
	if (rdr->type == REDIR_OUTPUT)
		return (file_open(rdr->file, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR));
	else if (rdr->type == REDIR_APPEND)
		return (file_open(rdr->file, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR));
	else
		ft_errmsg("error: get_dupout_fd\n");
	exit(EXIT_FAILURE);
}

// コマンドのパイプ入力を標準出力にする
void	pipin2stdout(t_dlist *cmdlst)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmdlst->cont;
	dup2(cmd->pipe[1], STDOUT_FILENO);
	cmd->pipe[1] = ft_close(cmd->pipe[1]);
}
