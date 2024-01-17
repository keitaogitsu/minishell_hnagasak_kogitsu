/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:07:17 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/17 19:03:37 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_builtin(char **argv, t_dlist **env_list)
{
	if (ft_strncmp(argv[0], "echo", 4) == 0)
		ft_echo(argv);
	else if (ft_strncmp(argv[0], "cd", 2) == 0)
		ft_cd(argv, env_list);
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
		// if (execve(cmd->path, cmd->argv, env_list) == -1)
		// 	perror("execve");
		// exit(EXIT_FAILURE);
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

// void	_dup_stdin(int i, int infile, int pipefd[2])
// {
// 	if (i == 0)
// 	{
// 		dup2(infile, STDIN_FILENO);
// 	}
// 	else
// 	{
// 		dup2(pipefd[0], STDIN_FILENO);
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 	}
// }

int	file_open(char *file, int flag, int mode)
{
	int	fd;

	fd = open(file, flag, mode);
	if (fd == -1)
	{
		printf("%s: %s\n", file, strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	get_dupin_fd(t_cmd *cmd)
{
	int		fd;
	t_dlist	*current;
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
		printf("error: get_dupin_fd\n");
	exit(EXIT_FAILURE);
}

int	get_dupout_fd(t_cmd *cmd)
{
	int		fd;
	t_dlist	*current;
	t_dlist	*last;
	t_redir	*rdr;

	last = cmd->output;
	while (last->nxt != NULL)
		last = last->nxt;
	rdr = (t_redir *)last->cont;
	if (rdr->type == REDIR_OUTPUT)
		return (file_open(rdr->file, O_WRONLY | O_CREAT | O_TRUNC,
				S_IRUSR | S_IWUSR));
	else if (rdr->type == REDIR_APPEND)
		return (file_open(rdr->file, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR));
	else
		printf("error: get_dupout_fd\n");
	exit(EXIT_FAILURE);
}

// 前コマンドのパイプ出力を標準入力にする
void	pipout2stdin(t_dlist *cmdlst)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmdlst->cont;
	dup2(cmd->pipe[0], STDIN_FILENO);
	close(cmd->pipe[0]);
	close(cmd->pipe[1]);
}

// コマンドのパイプ入力を標準出力にする
void	pipin2stdout(t_dlist *cmdlst)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmdlst->cont;
	dup2(cmd->pipe[1], STDOUT_FILENO);
	close(cmd->pipe[0]);
	close(cmd->pipe[1]);
}

void	dup_stdin(t_dlist *current)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	if (current->i == 0 && cmd->input == NULL)
	{
		// 前コマンドがない && 入力リダイレクトがない
		// 何もしない
	}
	else if (current->i == 0 && cmd->input != NULL)
	{
		// 前コマンドがない && 入力リダイレクトがある
		// 入力リダイレクトを実行
		dup2(get_dupin_fd(cmd), STDIN_FILENO);
	}
	else if (current->i != 0 && cmd->input == NULL)
	{
		// 前コマンドがある && 入力リダイレクトがない
		// 前コマンドのパイプ出力を入力にする
		// dup_pipout(current->prv);
		pipout2stdin(current->prv);
	}
	else if (current->i != 0 && cmd->input != NULL)
	{
		// 前コマンドがある && 入力リダイレクトがある
		// 入力リダイレクトを複製
		dup2(get_dupin_fd(cmd), STDIN_FILENO);
	}
}

void	dup_stdout(t_dlist *current)
{
	t_cmd	*cmd;

	printf("--- dup_stdout ---\n");

	cmd = (t_cmd *)current->cont;
	if (current->nxt == NULL && cmd->output == NULL)
	{
		// 次コマンドがない && 出力リダイレクトがない
		// 何もしない
	}
	else if (current->nxt == NULL && cmd->output != NULL)
	{
		// 次コマンドがない && 出力リダイレクトがある
		// 出力リダイレクトを実行
		dup2(get_dupout_fd(cmd), STDOUT_FILENO);
	}
	else if (current->nxt != NULL && cmd->output == NULL)
	{
		// 次コマンドがある && 出力リダイレクトがない
		// 出力先をパイプ入力にする
		// dup_pipout(current);
		pipin2stdout(current);
	}
	else if (current->nxt != NULL && cmd->output != NULL)
	{
		// 次コマンドがある && 出力リダイレクトがある
		// 出力リダイレクトを複製
		dup2(get_dupout_fd(cmd), STDOUT_FILENO);
	}
}


// set t_cmd->pipe
void	set_pipe(t_dlist *current)
{
	t_cmd	*cmd;

	printf("--- set_pipe ---\n");
	cmd = (t_cmd *)current->cont;
	if (cmd->pipe[0] != -1)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] != -1)
		close(cmd->pipe[1]);
	if (current->nxt != NULL)
	{
		if (pipe(cmd->pipe) == -1)
			perror("pipe error");
	}
	else {
		printf("unset pipe\n");
	}
}

// store stdin and stdout
void	store_stdio(t_dlist *current)
{
	t_cmd	*cmd;

	printf("--- store_stdio ---\n");
	cmd = (t_cmd *)current->cont;
	printf("1.stdio[0]: %d,stdio[1]: %d\n", cmd->stdio[0],cmd->stdio[1]);
	cmd->stdio[0] = dup(STDIN_FILENO);
	cmd->stdio[1] = dup(STDOUT_FILENO);
	if (cmd->stdio[0] == -1 || cmd->stdio[1] == -1)
	{
		perror("dup error");
		printf("2.stdio[0]: %d,stdio[1]: %d\n", cmd->stdio[0],cmd->stdio[1]);
		if (cmd->stdio[0] != -1)
			if (close(cmd->stdio[0]) == -1)
				perror("close error");
		exit(EXIT_FAILURE);
	}
}

void	restore_stdio(t_dlist *current)
{
	t_cmd	*cmd;
	int		res[2];

	cmd = (t_cmd *)current->cont;
	res[0] = dup2(cmd->stdio[0], STDIN_FILENO);
	res[1] = dup2(cmd->stdio[1], STDOUT_FILENO);
	if (res[0] != -1 && res[1] != -1)
	{
		if (close(cmd->stdio[0]) == -1)
			perror("close error");
		if (close(cmd->stdio[1]) == -1)
			perror("close error");
	}
}

void	exec_cmd_list(t_dlist **cmd_list, t_dlist **env_list)
{
	t_dlist *current;
	t_cmd *cmd;

	current = *cmd_list;
	printf("--- exec_cmd_list ---\n");
	while (current != NULL)
	{
		cmd = (t_cmd *)current->cont;
		if (is_builtin_cmd(cmd))
		{
			set_pipe(current);
			store_stdio(current);
			dup_stdin(current);
			dup_stdout(current);
			exec_builtin(cmd->argv, cmd->envp);
			restore_stdio(current);
		}
		else
		{
			// exec external command
			// 		pipe
			// 		fork
			// 		duplicate I/O
			dup_stdin(current);
			dup_stdout(current);
			//		execv
		}
		current = current->nxt;
	}
	// waitpide
}