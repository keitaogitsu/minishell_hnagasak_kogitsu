/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:00:02 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/30 05:50:51 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		g_signum = 0;

void	sig_hd(int signum)
{
	(void)signum;
	g_signum = SIGINT;
	ft_putstr_fd("\n", STDOUT_FILENO);
	close(STDIN_FILENO);
}

int	eof_handler(void)
{
	write(STDOUT_FILENO, "\033[A\033[2K\r> ", 10);
	return (1);
}

int	should_break(char *line, t_redir *redir, int *fd)
{
	char	*delim;

	if (g_signum == SIGINT)
	{
		close(*fd);
		*fd = file_open(redir->file, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR);
		return (1);
	}
	if (line == NULL && eof_handler())
		return (1);
	delim = ft_strtrim(redir->delimiter, "\"\'");
	if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		return (1);
	return (0);
}
