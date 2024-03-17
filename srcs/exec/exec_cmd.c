/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:07:17 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/17 21:42:27 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expander.h"
#include "free.h"

// void	exec_builtin(char **argv, t_dlist **env_list)
int	exec_builtin(t_cmd *cmd, t_dlist **env_list)
{
	ft_debug("[exec_builtin] %s\n", cmd->argv[0]);
	if (ft_strncmp(cmd->argv[0], "echo", 4) == 0)
		ft_echo(cmd->argv);
	else if (ft_strncmp(cmd->argv[0], "cd", 2) == 0)
		ft_cd(cmd->argv, env_list);
	else if (ft_strncmp(cmd->argv[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->argv[0], "exit", 4) == 0)
		ft_exit(cmd->argv);
	else if (ft_strncmp(cmd->argv[0], "env", 3) == 0)
		ft_env(cmd->argv, env_list);
	else if (ft_strncmp(cmd->argv[0], "export", 6) == 0)
		return (ft_export(cmd->argv, env_list));
	else if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
		ft_unset(cmd->argv, env_list);
	return (EXIT_SUCCESS); // あとで見直す
}

// return 1 if cmd is a builtin command
int	is_builtin_cmd(t_cmd *cmd)
{
	char	*cmd_name;

	cmd_name = cmd->argv[0];
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (1);
	else
		return (0);
}

int	exec_externalcmd(t_cmd *cmd, t_dlist **env_list)
{
	char	**env;
	char	**paths;

	ft_debug("[exec_externalcmd]: %s\n", cmd->argv[0]);
	env = envlist2arr(env_list);
	paths = get_paths(env_list);
	cmd->path = find_cmd_path(paths, cmd->argv[0]);
	free_strarr(paths);
	if (cmd->path == NULL)
		exit(EXIT_FAILURE);
	if (execve(cmd->path, cmd->argv, env) == -1)
	{
		perror("ft_execve");
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// char	*get_last_redir_file(t_dlist *redir_list)
// {
// 	t_dlist	*current;
// 	t_redir	*redir;

// 	current = redir_list;
// 	while (current->nxt != NULL)
// 		current = current->nxt;
// 	redir = (t_redir *)current->cont;
// 	return (redir->file);
// }

// void	stdin_from_file(char *file)
// {
// 	int	fd;

// 	fd = file_open(file, O_RDONLY, 0);
// 	dup2(fd, STDIN_FILENO);
// }

/**
 * Handles duplication of the standard output (stdout) for command execution.
 * The following rules are applied:
 * 1. If there is no next command and no output redirection,
	stdout remains unchanged.
 * 2. If there is no next command but there is output redirection,
	stdout is redirected
 *    to the specified file.
 * 3. If there is a next command but no output redirection,
	stdout is redirected to the
 *    write end of a pipe for inter-command communication.
 * 4. If there is both a next command and output redirection,
	stdout is redirected
 *    to the specified file, ignoring the pipe to the next command.
	* @param current pointer to the current command in t_dlist of commands.
 */

// size_t	count_cmd_list(t_dlist **cmd_list)
// {
// 	size_t	count;
// 	t_dlist	*current;

// 	count = 0;
// 	current = *cmd_list;
// 	while (current != NULL)
// 	{
// 		count++;
// 		current = current->nxt;
// 	}
// 	return (count);
// }

// 組み込みコマンドまたは外部コマンドを実行する
void	exec_cmd(t_cmd *cmd, t_dlist **env_list)
{
	int	exit_status;

	exit_status = 0;
	if (is_builtin_cmd(cmd))
	{
		exit_status = exec_builtin(cmd, cmd->envp);
		exit(exit_status);
	}
	else
	{
		exec_externalcmd(cmd, env_list);
	}
}

// char	*expand_heredoc(char *str, t_dlist **env_list)
// {
// 	char	*env_value;
// 	char	*replaced_str;
// 	char	*str_head;

// 	ft_debug("--- expand_heredoc %s ---\n", str);
// 	str_head = str;
// 	while (*str != '\0')
// 	{
// 		env_value = find_env_value(str, *env_list);
// 		if (env_value != NULL)
// 		{
// 			replaced_str = replace_1st_env_var(str_head, env_value);
// 			free(str_head);
// 			str_head = replaced_str;
// 			str = replaced_str;
// 		}
// 		else
// 			str++;
// 	}
// 	return (str_head);
// }
