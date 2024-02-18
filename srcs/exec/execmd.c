/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:07:17 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/18 16:24:14 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// ファイルディスクリプタを閉じる。成功したら初期値(-1)を返す。
// 失敗したら引数のfdをそのまま返す
int	ft_close(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
		{
			perror("ft_close error::");
			return (fd);
		}
		else
		{
			ft_debug("close fd:%d\n", fd);
			return (-1);
		}
	}
	return (fd);
}

void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		perror("pipe error");
	else
		ft_debug("  set pipe[0]:%d pipe[1]:%d\n", fd[0], fd[1]);
}

// void	exec_builtin(char **argv, t_dlist **env_list)
void	exec_builtin(t_cmd *cmd, t_dlist **env_list)
{
	ft_debug("--- exec_builtin [%s]---\n", cmd->argv[0]);
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
		ft_export(cmd->argv, env_list);
	else if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
		ft_unset(cmd->argv, env_list);
}

// return 1 if cmd is a builtin command
int	is_builtin_cmd(t_cmd *cmd)
{
	char	*cmd_name;

	ft_debug("--- is_builtin_cmd [%s]---\n", cmd->argv[0]);
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

// パスとコマンド名を連結した文字列を返す
char	*cat_path(char *path, char *cmd)
{
	char	*cat_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	cat_path = ft_strjoin(tmp, cmd);
	free(tmp);
	return (cat_path);
}

// 外部コマンドのパスを探し、コマンド名を連結して返す
// paths: PATHを:で分割した文字列配列
// cmd: 検索するコマンド名
char	*find_cmd_path(char *paths[], char *cmd)
{
	int		i;
	char	*cmd_path;

	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		printf("%s: No such file or directory\n", cmd);
		return (NULL);
	}
	i = 0;
	while (paths[i] != NULL)
	{
		cmd_path = cat_path(paths[i], cmd);
		if (access(cmd_path, X_OK) == 0)
		{
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	printf("%s: command not found\n", cmd);
	return (NULL);
}

char	**get_paths(t_dlist **env_list)
{
	t_dlist	*current;
	t_env	*env;
	char	**paths;
	char	*path;

	// char	*tmp;
	// int		i;
	current = *env_list;
	// 環境変数PATHを探す
	while (current != NULL)
	{
		env = (t_env *)current->cont;
		if (ft_strncmp(env->key, "PATH", 5) == 0)
		{
			path = ft_strdup(env->value);
			break ;
		}
		current = current->nxt;
	}
	// PATHを:で分割
	paths = ft_split(path, ':');
	// i = 0;
	// while (paths[i] != NULL)
	// {
	// 	tmp = ft_strtrim(paths[i], " ");
	// 	free(paths[i]);
	// 	paths[i] = tmp;
	// 	i++;
	// }
	free(path);
	return (paths);
}

/**
 * @brief free a NULL-terminated char double pointer.
 * @param arr NULL-terminated char double pointer
 * @note double pointer must be NULL-terminated.
 */
void	free_strarr(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	ft_execmd(t_cmd *cmd, t_dlist **env_list)
{
	char	**env;
	char	**paths;

	ft_debug("--- ft_execmd [%s]---\n", cmd->argv[0]);
	env = envlist2arr(env_list);
	paths = get_paths(env_list);
	cmd->path = find_cmd_path(paths, cmd->argv[0]);
	free_strarr(paths);
	ft_debug("cmd->path:%s\n", cmd->path);
	if (execve(cmd->path, cmd->argv, env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}

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

// コマンドの最後の出力リダイレクションに対応するファイルを開き、そのファイルディスクリプタを返す。
// リダイレクションのタイプに応じて、ファイルを上書きまたは追記モードで開く。
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
}

// コマンドのパイプ入力を標準出力にする
void	pipin2stdout(t_dlist *cmdlst)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmdlst->cont;
	dup2(cmd->pipe[1], STDOUT_FILENO);
	// close(cmd->pipe[0]);
	close(cmd->pipe[1]);
}

// リダイレクトやパイプに応じて標準入力を書き換える
void	dup_stdin(t_dlist *current)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	fprintf(stderr, "--- dup_stdin [%s]---\n", cmd->argv[0]);
	if (current->i == 0 && cmd->input == NULL)
	{
		// 前コマンドがない && 入力リダイレクトがない
		// 標準入力のまま、何もしない
		ft_debug("  Not dup stdin\n");
	}
	else if (current->i == 0 && cmd->input != NULL)
	{
		// 前コマンドがない && 入力リダイレクトがある
		// 入力リダイレクトを入力にする
		ft_debug("  dup input redirection\n");
		dup2(get_dupin_fd(cmd), STDIN_FILENO);
	}
	else if (current->i != 0 && cmd->input == NULL)
	{
		// 前コマンドがある && 入力リダイレクトがない
		// 前コマンドの出力を入力にする
		ft_debug("  dup pipout2stdin\n");
		pipout2stdin(current->prv);
	}
	else if (current->i != 0 && cmd->input != NULL)
	{
		// 前コマンドがある && 入力リダイレクトがある
		// 入力リダイレクトを入力にする
		ft_debug("  dup input redirection\n");
		dup2(get_dupin_fd(cmd), STDIN_FILENO);
	}
}

// リダイレクトやパイプに応じて標準出力を書き換える
void	dup_stdout(t_dlist *current)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	ft_debug("--- dup_stdout [%s]---\n", cmd->argv[0]);
	if (current->nxt == NULL && cmd->output == NULL)
	{
		// 次コマンドがない && 出力リダイレクトがない
		// 標準出力のまま、何もしない
		ft_debug("  Not dup stdout\n");
	}
	else if (current->nxt == NULL && cmd->output != NULL)
	{
		// 次コマンドがない && 出力リダイレクトがある
		// 出力リダイレクトに出力する
		ft_debug("  dup output redirection 1\n");
		dup2(get_dupout_fd(cmd), STDOUT_FILENO);
	}
	else if (current->nxt != NULL && cmd->output == NULL)
	{
		// 次コマンドがある && 出力リダイレクトがない
		// パイプの書き込み側に出力する
		ft_debug("  dup pipin2stdout\n");
		pipin2stdout(current);
	}
	else if (current->nxt != NULL && cmd->output != NULL)
	{
		// 次コマンドがある && 出力リダイレクトがある
		// 出力リダイレクトに出力する
		ft_debug("  dup output redirection 2\n");
		dup2(get_dupout_fd(cmd), STDOUT_FILENO);
	}
}

// 次のコマンドが存在する場合、pipeを作成する
void	set_pipe_if_needed(t_dlist *current)
{
	t_cmd	*cmd;

	ft_debug("--- set_pipe_if_needed ---\n");
	cmd = (t_cmd *)current->cont;
	cmd->pipe[0] = ft_close(cmd->pipe[0]); // 初期化
	cmd->pipe[1] = ft_close(cmd->pipe[1]); // 初期化
	if (current->nxt != NULL)
		ft_pipe(cmd->pipe);
	else
		ft_debug("  unset pipe\n");
}

// 標準入出力を保存しておく
void	store_stdio(t_dlist *current)
{
	t_cmd	*cmd;

	ft_debug("--- store_stdio ---\n");
	cmd = (t_cmd *)current->cont;
	cmd->stdio[0] = dup(STDIN_FILENO);
	cmd->stdio[1] = dup(STDOUT_FILENO);
	if (cmd->stdio[0] == -1 || cmd->stdio[1] == -1)
	{
		perror("dup error");
		ft_debug("stdio[0]: %d,stdio[1]: %d\n", cmd->stdio[0], cmd->stdio[1]);
		if (cmd->stdio[0] != -1)
			// if (close(cmd->stdio[0]) == -1)
			// 	perror("close error");
			exit(EXIT_FAILURE);
	}
	else
	{
		printf("stdio[0]: %d,stdio[1]: %d\n", cmd->stdio[0], cmd->stdio[1]);
	}
}

void	restore_stdio(t_dlist *current)
{
	t_cmd	*cmd;
	int		res[2];

	ft_debug("--- restore_stdio ---\n");
	cmd = (t_cmd *)current->cont;
	res[0] = dup2(cmd->stdio[0], STDIN_FILENO);
	res[1] = dup2(cmd->stdio[1], STDOUT_FILENO);
	if (res[0] != -1 && res[1] != -1)
	{ // 復元できたら複製していた標準入出力を閉じる
		ft_close(cmd->stdio[0]);
		ft_close(cmd->stdio[1]);
	}
}

size_t	count_cmd_list(t_dlist **cmd_list)
{
	size_t	count;
	t_dlist	*current;

	count = 0;
	current = *cmd_list;
	while (current != NULL)
	{
		count++;
		current = current->nxt;
	}
	return (count);
}

// 外部コマンドまたは次のコマンドがある場合、子プロセスを作成する
void	set_fork_if_needed(t_dlist *current)
{
	t_cmd	*cmd;

	ft_debug("--- set_fork_if_needed ---\n");
	cmd = (t_cmd *)current->cont;
	if (!is_builtin_cmd(cmd) || current->nxt != NULL)
	{
		// printf("is_builtin_cmd:%d\n",is_builtin_cmd(cmd));
		// printf("current->nxt:%p\n",current->nxt);
		printf("  should fork\n");
		cmd->pid = fork();
	}
	else
		printf("  no fork\n");
}

// 組み込みコマンドまたは外部コマンドを実行する
void	exec_cmd(t_cmd *cmd, t_dlist **env_list)
{
	ft_debug("--- exec_cmd ---\n");
	if (is_builtin_cmd(cmd))
	{
		exec_builtin(cmd, cmd->envp);
		exit(EXIT_SUCCESS);
	}
	else
		ft_execmd(cmd, env_list);
}

// wait for all child processes to finish
void	wait_children(t_dlist **cmd_list)
{
	t_dlist	*current;
	t_cmd	*cmd;

	current = *cmd_list;
	while (current != NULL)
	{
		cmd = (t_cmd *)current->cont;
		waitpid(cmd->pid, NULL, 0);
		fprintf(stderr, "waitpid %d\n", cmd->pid);
		current = current->nxt;
	}
}

void	exec_single_builtin(t_dlist *current, t_dlist **env_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	fprintf(stderr, "--- exec_single_builtin [%s]---\n", cmd->argv[0]);
	store_stdio(current);
	dup_stdin(current);
	dup_stdout(current);
	exec_builtin(cmd, cmd->envp);
	restore_stdio(current);
}

void	close_parent_pipe(t_dlist *current)
{
	t_cmd	*cmd;
	t_cmd	*prv_cmd;

	cmd = (t_cmd *)current->cont;
	fprintf(stderr, "--- close_parent_pipe [%s]---\n", cmd->argv[0]);
	if (current->nxt != NULL)
	{
		cmd->pipe[1] = ft_close(cmd->pipe[1]);
	}
	if (current->prv != NULL)
	{
		prv_cmd = (t_cmd *)current->prv->cont;
		prv_cmd->pipe[0] = ft_close(prv_cmd->pipe[0]);
	}
}

void	exec_cmd_list(t_dlist **cmd_list, t_dlist **env_list)
{
	t_dlist *current;
	t_cmd *cmd;
	int has_next_cmd;
	int is_builtin;

	fprintf(stderr, "--- exec_cmd_list ---\n");
	current = *cmd_list;

	is_builtin = is_builtin_cmd((t_cmd *)current->cont);
	has_next_cmd = (current->nxt != NULL);

	if (is_builtin && !has_next_cmd)
		exec_single_builtin(current, env_list);
	else
	{
		while (current != NULL)
		{
			cmd = (t_cmd *)current->cont;
			printf("########## %s ##########\n", cmd->argv[0]);
			set_pipe_if_needed(current);
			cmd->pid = fork();
			if (cmd->pid == 0)
			{
				ft_close(cmd->pipe[0]);
				dup_stdin(current);
				dup_stdout(current);
				exec_cmd(cmd, env_list);
			}
			else if (cmd->pid > 0)
			{
				close_parent_pipe(current);
				// waitpid(cmd->pid, NULL, 0);
				// fprintf(stderr, "  # waitpid %d\n", cmd->pid);
			}
			else
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			current = current->nxt;
		}
		wait_children(cmd_list);
	}
}