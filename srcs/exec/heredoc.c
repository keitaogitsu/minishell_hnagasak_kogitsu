/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:00:02 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/07 02:08:04 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expander.h"
#include "free.h"

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

void	input_heredocs(t_cmd *cmd, t_dlist **env_list)
{
	t_dlist	*current;
	t_redir	*rdr;

	current = cmd->input;
	while (current != NULL)
	{
		rdr = (t_redir *)current->cont;
		if (rdr->type == REDIR_HEREDOC)
		{
			ft_debug("### input_heredoc [%s]\n", rdr->file);
			ft_heredoc(cmd, rdr, env_list);
		}
		current = current->nxt;
	}
}

char	*expand_heredoc(char *str, t_dlist **env_list)
{
	char	*env_value;
	char	*replaced_str;
	char	*str_head;

	ft_debug("--- expand_heredoc %s ---\n", str);
	str_head = str;
	while (*str != '\0')
	{
		env_value = find_env_value(str, *env_list);
		if (env_value != NULL)
		{
			replaced_str = replace_1st_env_var(str_head, env_value);
			free(str_head);
			str_head = replaced_str;
			str = replaced_str;
		}
		else
			str++;
	}
	return (str_head);
}

void	input_hd(t_cmd *cmd, t_redir *redir, int fd, t_dlist **env_list)
{
	char	*line;
	int		delimitype;
	char	*delim;

	delimitype = get_delimiter_type(redir->delimiter);
	line = ft_malloc(1);
	while (line != NULL)
	{
		line = ft_free(line);
		dup2(cmd->stdio[0], STDIN_FILENO);
		line = readline("> ");
		if (line == NULL)
			break ;
		delim = ft_strtrim(redir->delimiter, "\"\'");
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
			break ;
		if (delimitype == NOT_IN_QUOTE)
			line = expand_heredoc(line, env_list);
		ft_putendl_fd(line, fd);
	}
	ft_free(line);
}

void	ft_heredoc(t_cmd *cmd, t_redir *redir, t_dlist **env_list)
{
	int	fd;

	ft_debug("----- ft_heredoc [%s]-----\n", redir->file);
	fd = file_open(redir->file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR);
	input_hd(cmd, redir, fd, env_list);
	close(fd);
	fd = file_open(redir->file, O_RDONLY, 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
