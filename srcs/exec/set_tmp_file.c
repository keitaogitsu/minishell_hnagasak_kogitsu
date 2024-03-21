/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tmp_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 01:52:45 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/22 06:23:28 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// tmpファイル名を生成する
char	*generate_tmpfile_name(size_t cmd_idx, size_t redir_idx)
{
	char	*tmp;
	char	*file_name;
	char	*cmd_idx_str;
	char	*redir_idx_str;

	ft_debug("----- generate_tmpfile_name -----\n");
	cmd_idx_str = ft_itoa(cmd_idx);
	redir_idx_str = ft_itoa(redir_idx);
	file_name = ft_strjoin("tmp", cmd_idx_str);
	tmp = ft_strjoin(file_name, "-");
	free(file_name);
	file_name = ft_strjoin(tmp, redir_idx_str);
	free(tmp);
	free(cmd_idx_str);
	free(redir_idx_str);
	ft_debug("  file_name: %s\n", file_name);
	return (file_name);
}

void	set_tmpfile_name(t_cmd *cmd, size_t cmd_idx)
{
	t_dlist	*current;
	t_redir	*redir;

	current = cmd->input;
	while (current != NULL)
	{
		redir = (t_redir *)current->cont;
		if (redir->type == REDIR_HEREDOC)
			redir->file = generate_tmpfile_name(cmd_idx, current->i);
		current = current->nxt;
	}
}

/**
 * @brief deletes tmp files created by Heredoc redirections.
 * @param cmd pointer to t_cmd, containing the input redirections.
 */
void	delete_tmp_files(t_cmd *cmd)
{
	t_dlist	*current;
	t_redir	*redir;

	current = cmd->input;
	while (current != NULL)
	{
		redir = (t_redir *)current->cont;
		if (redir->type == REDIR_HEREDOC)
			delete_file(redir->file);
		current = current->nxt;
	}
}
