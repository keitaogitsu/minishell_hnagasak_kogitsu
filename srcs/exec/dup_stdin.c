/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_stdin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:43:16 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/07 01:48:16 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// リダイレクトやパイプに応じて標準入力を書き換える
void	dup_stdin(t_dlist *current)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	if (current->prv == NULL && cmd->input == NULL)
		ft_debug("[dup_stdin]  %s: Not dup stdin\n", cmd->argv[0]);
	else if (current->prv == NULL && cmd->input != NULL)
		dup2(get_dupin_fd(cmd), STDIN_FILENO);
	else if (current->prv != NULL && cmd->input == NULL)
		pipout2stdin(current->prv);
	else if (current->prv != NULL && cmd->input != NULL)
		dup2(get_dupin_fd(cmd), STDIN_FILENO);
}

// 指定したコマンドの最後の入力リダイレクションのfdを返す。
int	get_dupin_fd(t_cmd *cmd)
{
	t_dlist	*last;
	t_redir	*rdr;

	last = cmd->input;
	while (last->nxt != NULL)
		last = last->nxt;
	rdr = (t_redir *)last->cont;
	if (rdr->type == REDIR_INPUT)
		return (file_open(rdr->file, O_RDONLY, 0));
	else if (rdr->type == REDIR_HEREDOC)
		return (STDIN_FILENO);
	else
		ft_errmsg("error: get_dupin_fd\n");
	exit(EXIT_FAILURE);
}

// 前コマンドのパイプ出力を標準入力にする
void	pipout2stdin(t_dlist *cmdlst)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmdlst->cont;
	dup2(cmd->pipe[0], STDIN_FILENO);
	close(cmd->pipe[0]);
}
