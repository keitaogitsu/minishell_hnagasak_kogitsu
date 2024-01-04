/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:07:17 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/02 18:07:24 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_builtin(char **argv, t_dlist **env_list)
{
	if (ft_strncmp(argv[0], "echo", 4) == 0)
		ft_echo(argv);
	else if (ft_strncmp(argv[0], "cd", 2) == 0)
		ft_cd(argv);
	else if (ft_strncmp(argv[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(argv[0], "exit", 4) == 0)
		ft_exit(argv);
	else if (ft_strncmp(argv[0], "env", 3) == 0)
		ft_env(argv, env_list);
	else if (ft_strncmp(argv[0], "export", 6) == 0)
		ft_export(argv, env_list);
	else if (ft_strncmp(argv[0], "unset", 5) == 0)
		ft_unset(argv, env_list);
}

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

int	ft_execmd(t_cmd *cmd, t_dlist **env_list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		// 標準入出力のduplication
		// if (cmd->input == REDIR_INPUT)
		// 	dup2(cmd->input_fd, STDIN_FILENO);
		// if (cmd->output == REDIR_OUTPUT)
		// 	dup2(cmd->output_fd, STDOUT_FILENO);
		// if (cmd->output == REDIR_APPEND)
		// 	dup2(cmd->output_fd, STDOUT_FILENO);
		// if (cmd->output == REDIR_HEREDOC)
		// 	dup2(cmd->output_fd, STDOUT_FILENO);
		// コマンド実行
		if (execve(cmd->path, cmd->argv, env_list) == -1)
			perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (status);
	}
	else
		perror("fork");
	return (0);
}

void	exec_cmd_list(t_list **cmd_list, t_dlist **env_list)
{
	t_dlist *current;
	t_cmd *cmd;
	int status;

	current = *cmd_list;
	while (current != NULL)
	{
		cmd = (t_cmd *)current->cont;
		if (is_builtin_cmd(cmd))
		{
			exec_builtin(cmd->argv, cmd->envp);
		}
		else
		{
			// exec external command
			// 		pipe
			// 		fork
			// 		duplicate I/O
			//		execv
		}
		current = current->nxt;
	}
	// waitpide
}