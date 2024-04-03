/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:00:02 by hnagasak          #+#    #+#             */
/*   Updated: 2024/04/04 05:13:14 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expander.h"
#include "free.h"
#include "signal_handlers.h"

// delimiterがダブルクォートまたはシングルクォートで囲まれているかを判定する
int	get_delimiter_type(char *delimiter)
{
	size_t	len;

	len = ft_strlen(delimiter);
	if (len < 2)
		return (NOT_IN_QUOTE);
	if (delimiter[0] == '"' && delimiter[len - 1] == '"')
		return (IN_DQUOTE);
	else if (delimiter[0] == '\'' && delimiter[len - 1] == '\'')
		return (IN_QUOTE);
	else
		return (NOT_IN_QUOTE);
}

char	*expand_heredoc(char *str, t_dlist **env_list, int exit_status)
{
	char	*env_value;
	char	*str_head;

	ft_debug("--- expand_heredoc %s ---\n", str);
	str_head = str;
	while (*str != '\0')
	{
		if (ft_strncmp(str, "$?", ft_strlen("$?")) == 0)
			replace_exit_status(&str_head, &str, exit_status);
		else
		{
			env_value = find_env_value(str, *env_list);
			if (env_value != NULL)
				replace_env_value(&str_head, &str, env_value);
		}
		str++;
	}
	return (str_head);
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
	if (line == NULL && eof_handler_in_heredoc())
		return (1);
	delim = ft_strtrim(redir->delimiter, "\"\'");
	if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		return (1);
	return (0);
}

void	input_hd(t_cmd *cmd, t_redir *redir, t_dlist **env_list,
		int exit_status)
{
	char	*line;
	int		delimitype;
	int		fd;

	fd = file_open(redir->file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	delimitype = get_delimiter_type(redir->delimiter);
	line = ft_malloc(1);
	signal(SIGINT, sigint_handler_in_heredoc);
	g_signum = 0;
	while (line != NULL)
	{
		line = ft_free(line);
		dup2(cmd->stdio[0], STDIN_FILENO);
		line = readline("> ");
		if (should_break(line, redir, &fd))
			break ;
		if (delimitype == NOT_IN_QUOTE)
			line = expand_heredoc(line, env_list, exit_status);
		ft_putendl_fd(line, fd);
	}
	ft_free(line);
	close(fd);
}

void	input_heredocs(t_cmd *cmd, t_dlist **env_list, int exit_status)
{
	t_dlist	*current;
	t_redir	*redir;
	int		fd;

	current = cmd->input;
	while (current != NULL)
	{
		redir = (t_redir *)current->cont;
		if (redir->type == REDIR_HEREDOC)
		{
			// ft_heredoc(cmd, redir, env_list, exit_status);
			input_hd(cmd, redir, env_list, exit_status);
			fd = file_open(redir->file, O_RDONLY, 0);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		current = current->nxt;
	}
}
