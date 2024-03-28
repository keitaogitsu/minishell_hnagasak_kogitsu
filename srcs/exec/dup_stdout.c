/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_stdout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:45:53 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/28 10:04:03 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "utils.h"

int	dup_output_redir(t_cmd *cmd)
{
	int	fd;

	ft_debug("[dup_output_redir] dup output redir: ");
	fd = get_dupout_fd(cmd);
	if (fd == -1)
		return (EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	ft_debug("%d\n", fd);
	return (EXIT_SUCCESS);
}

int	dup_stdout(t_dlist *current)
{
	t_cmd	*cmd;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	cmd = (t_cmd *)current->cont;
	if (current->nxt == NULL && cmd->output == NULL)
		ft_debug("[dup_stdout] %s: Not dup stdout\n", cmd->argv[0]);
	else if (current->nxt == NULL && cmd->output != NULL)
		exit_status = dup_output_redir(cmd);
	else if (current->nxt != NULL && cmd->output == NULL)
	{
		pipin2stdout(current);
		ft_debug("[dup_stdout] %s: dup pipin2stdout\n", cmd->argv[0]);
	}
	else if (current->nxt != NULL && cmd->output != NULL)
		exit_status = dup_output_redir(cmd);
	return (exit_status);
}

int	redir_open(t_dlist *redirects)
{
	t_redir	*rdr;
	int		fd;

	rdr = (t_redir *)redirects->cont;
	fd = file_open(rdr->file, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
		return (-1);
	close(fd);
	return (0);
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
		if (redir_open(last) == -1)
			return (-1);
		last = last->nxt;
	}
	rdr = (t_redir *)last->cont;
	if (rdr->type == REDIR_OUTPUT)
		return (file_open(rdr->file, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR));
	else if (rdr->type == REDIR_APPEND)
		return (file_open(rdr->file, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR));
	else
		ft_errmsg("error: invalid output redir type\n");
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
