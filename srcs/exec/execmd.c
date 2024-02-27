/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:07:17 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/28 08:16:44 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expander.h"

int	delete_file(const char *filepath)
{
	ft_debug("--- delete_file [%s]---\n", filepath);
	if (unlink(filepath) == 0)
	{
		ft_debug("'%s' が正常に削除されました。\n", filepath);
		return (0); // 成功
	}
	else
	{
		perror("ファイルの削除に失敗しました");
		return (-1); // エラー
	}
}

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
			ft_debug("    close fd:%d\n", fd);
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
		ft_debug("[set_pipe] fd(%d,%d)\n", fd[0], fd[1]);
}

// void	exec_builtin(char **argv, t_dlist **env_list)
void	exec_builtin(t_cmd *cmd, t_dlist **env_list)
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
		ft_export(cmd->argv, env_list);
	else if (ft_strncmp(cmd->argv[0], "unset", 5) == 0)
		ft_unset(cmd->argv, env_list);
}

// return 1 if cmd is a builtin command
int	is_builtin_cmd(t_cmd *cmd)
{
	char	*cmd_name;

	// ft_debug("--- is_builtin_cmd [%s]---\n", cmd->argv[0]);
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
	ft_errmsg("minishell: ");
	ft_errmsg(cmd);
	ft_errmsg(": command not found\n");
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
	path = NULL;
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
	paths = ft_split(path, ':');
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

// コマンドの最後の出力リダイレクションに対応するファイルを開き、そのファイルディスクリプタを返す。
// リダイレクションのタイプに応じて、ファイルを上書きまたは追記モードで開く。
int	get_dupout_fd(t_cmd *cmd)
{
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
		ft_errmsg("error: get_dupout_fd\n");
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
	int		fd;

	cmd = (t_cmd *)current->cont;
	if (current->prv == NULL && cmd->input == NULL)
		ft_debug("[dup_stdin]  %s: Not dup stdin\n", cmd->argv[0]);
	else if (current->prv == NULL && cmd->input != NULL)
	{
		fd = get_dupin_fd(cmd);
		dup2(fd, STDIN_FILENO);
		ft_debug("[dup_stdin]  %s: dup input redir (%d)\n", cmd->argv[0], fd);
	}
	else if (current->prv != NULL && cmd->input == NULL)
	{
		pipout2stdin(current->prv);
		ft_debug("[dup_stdin]  %s: dup pipout2stdin\n", cmd->argv[0]);
	}
	else if (current->prv != NULL && cmd->input != NULL)
	{
		fd = get_dupin_fd(cmd);
		dup2(fd, STDIN_FILENO);
		ft_debug("[dup_stdin]  %s: dup input redir (%d)\n", cmd->argv[0], fd);
	}
}

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
	* @param current A pointer to the current command in the doubly linked list of commands.
 */
void	dup_stdout(t_dlist *current)
{
	t_cmd	*cmd;
	int		fd;

	cmd = (t_cmd *)current->cont;
	// ft_debug("--- dup_stdout [%s]---\n", cmd->argv[0]);
	if (current->nxt == NULL && cmd->output == NULL)
	{
		ft_debug("[dup_stdout] %s: Not dup stdout\n", cmd->argv[0]);
	}
	else if (current->nxt == NULL && cmd->output != NULL)
	{
		fd = get_dupout_fd(cmd);
		dup2(fd, STDOUT_FILENO);
		ft_debug("[dup_stdout] %s: dup output redir (%d)\n", cmd->argv[0], fd);
	}
	else if (current->nxt != NULL && cmd->output == NULL)
	{
		pipin2stdout(current);
		ft_debug("[dup_stdout] %s: dup pipin2stdout\n", cmd->argv[0]);
	}
	else if (current->nxt != NULL && cmd->output != NULL)
	{
		fd = get_dupout_fd(cmd);
		dup2(fd, STDOUT_FILENO);
		ft_debug("[dup_stdout] %s: dup output redir (%d)\n", cmd->argv[0], fd);
	}
}

// 次のコマンドが存在する場合、pipeを作成する
void	set_pipe_if_needed(t_dlist *current)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	cmd->pipe[0] = ft_close(cmd->pipe[0]); // 初期化
	cmd->pipe[1] = ft_close(cmd->pipe[1]); // 初期化
	if (current->nxt != NULL)
		ft_pipe(cmd->pipe);
	else
		ft_debug("[set_pipe] unset pipe\n");
}

// 標準入出力を保存しておく
void	store_stdio(t_dlist *current)
{
	t_cmd	*cmd;

	// ft_debug("--- store_stdio ---\n");
	cmd = (t_cmd *)current->cont;
	cmd->stdio[0] = dup(STDIN_FILENO);
	cmd->stdio[1] = dup(STDOUT_FILENO);
	if (cmd->stdio[0] == -1 || cmd->stdio[1] == -1)
	{
		perror("[store_stdio] dup error");
		ft_debug("[store_stdio] stdio(%d,%d)\n", cmd->stdio[0], cmd->stdio[1]);
		ft_close(cmd->stdio[0]);
		ft_close(cmd->stdio[1]);
	}
	else
		ft_debug("[store_stdio] stdio(%d,%d)\n", cmd->stdio[0], cmd->stdio[1]);
}

void	restore_stdio(t_dlist *current)
{
	t_cmd	*cmd;
	int		res[2];

	cmd = (t_cmd *)current->cont;
	ft_debug("[restore_stdio] (%d,%d)\n", cmd->stdio[0], cmd->stdio[1]);
	res[0] = dup2(cmd->stdio[0], STDIN_FILENO);
	res[1] = dup2(cmd->stdio[1], STDOUT_FILENO);
	if (res[0] != -1 && res[1] != -1)
	{
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
		ft_debug("  should fork\n");
		cmd->pid = fork();
	}
	else
		ft_debug("  No fork\n");
}

// 組み込みコマンドまたは外部コマンドを実行する
void	exec_cmd(t_cmd *cmd, t_dlist **env_list)
{
	if (is_builtin_cmd(cmd))
	{
		exec_builtin(cmd, cmd->envp);
		exit(EXIT_SUCCESS);
	}
	else
	{
		exec_externalcmd(cmd, env_list);
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
		ft_debug("[waitpid] %d: %d.%s\n", cmd->pid, current->i, cmd->argv[0]);
		delete_tmp_files(cmd);
		current = current->nxt;
	}
}

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

char	*expand_heredoc(char *str, t_dlist **env_list)
{
	char	*env_value;
	char	*replaced_str;
	char	*str_head;

	// size_t	state;
	// int		is_replaced_str;
	ft_debug("--- expand_heredoc %s ---\n", str);
	// is_replaced_str = 0;
	// state = NOT_IN_QUOTE;
	str_head = str;
	while (*str != '\0')
	{
		env_value = find_env_value(str, *env_list);
		if (env_value != NULL)
		{
			replaced_str = replace_1st_env_var(str_head, env_value);
			free(str_head);
			str_head = replaced_str;
			// state = NOT_IN_QUOTE;
			str = replaced_str;
		}
		else
			str++;
	}
	return (str_head);
}

void	ft_heredoc(t_redir *redir, t_dlist **env_list)
{
	char	*line;
	int		fd;
	int		delimitype;
	char	*delim;

	ft_debug("----- ft_heredoc [%s]-----\n", redir->file);
	fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror("file open error");
		exit(EXIT_FAILURE);
	}
	delimitype = get_delimiter_type(redir->delimiter);
	line = "";
	while (line != NULL)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		delim = ft_strtrim(redir->delimiter, "\"\'");
		if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
		{
			ft_debug("  delimiter found\n");
			break ;
		}
		if (delimitype == NOT_IN_QUOTE)
			line = expand_heredoc(line, env_list);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror("file open error2");
		exit(EXIT_FAILURE);
	}
	if (line != NULL)
	{
		ft_debug("  LINE2:%s\n", line);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
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
			ft_heredoc(rdr, env_list);
		}
		current = current->nxt;
	}
}

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

void	create_tmp_files(t_cmd *cmd, size_t cmd_idx)
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

void	exec_single_builtin(t_dlist *current, t_dlist **env_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)current->cont;
	ft_debug("--- exec_single_builtin %s ---\n", cmd->argv[0]);
	create_tmp_files(cmd, current->i);
	store_stdio(current);
	dup_stdin(current);
	dup_stdout(current);
	input_heredocs(cmd, env_list);
	exec_builtin(cmd, env_list);
	delete_tmp_files(cmd);
	restore_stdio(current);
}

void	close_parent_pipe(t_dlist *current)
{
	t_cmd	*cmd;
	t_cmd	*prv_cmd;

	cmd = (t_cmd *)current->cont;
	if (current->nxt != NULL)
	{
		ft_debug("[close_parent_pipe] close %d\n", cmd->pipe[1]);
		cmd->pipe[1] = ft_close(cmd->pipe[1]);
	}
	if (current->prv != NULL)
	{
		prv_cmd = (t_cmd *)current->prv->cont;
		ft_debug("[close_parent_pipe] close %d\n", prv_cmd->pipe[0]);
		prv_cmd->pipe[0] = ft_close(prv_cmd->pipe[0]);
	}
}

void	exec_cmd_list(t_dlist **cmd_list, t_dlist **env_list)
{
	t_dlist *current;
	t_cmd *cmd;
	int has_next_cmd;
	int is_builtin;

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
			// ft_debug("[exec_cmd_list] %s\n", cmd->argv[0]);
			ft_debug("\n--- exec_cmd[%d]: %s ---\n", current->i, cmd->argv[0]);
			set_pipe_if_needed(current);
			create_tmp_files(cmd, current->i);
			cmd->pid = fork();
			if (cmd->pid == 0)
			{
				ft_debug("[child process] close pipin fd:%d\n", cmd->pipe[0]);
				ft_close(cmd->pipe[0]);
				dup_stdin(current);
				input_heredocs(cmd, env_list);
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