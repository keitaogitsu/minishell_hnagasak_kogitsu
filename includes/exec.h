/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:07:35 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/22 06:23:10 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtin.h"
# include "debug.h"
# include "libft.h"
# include "utils.h"
# include <fcntl.h>

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
	char			*delimiter;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_dlist			**envp;
	char			*path;
	t_dlist			*input;
	t_dlist			*output;
	int				pipe[2];
	int				stdio[2];
	int				pid;
}					t_cmd;

// dup_stdin.c
void				dup_stdin(t_dlist *current);
int					get_dupin_fd(t_cmd *cmd);
void				pipout2stdin(t_dlist *cmdlst);
// dup_stdout.c
void				dup_stdout(t_dlist *current);
int					get_dupout_fd(t_cmd *cmd);
void				pipin2stdout(t_dlist *cmdlst);
// exec_cmd.c
void				exec_cmd(t_cmd *cmd, t_dlist **env_list);
int					is_builtin_cmd(t_cmd *cmd);
int					exec_builtin(t_cmd *cmd, t_dlist **env_list);
int					exec_externalcmd(t_cmd *cmd, t_dlist **env_list);
// exec_cmd_list.c
void				exec_cmd_list(t_dlist **cmd_list, t_dlist **env_list,
						int *exit_status);
int					exec_single_builtin(t_dlist *current, t_dlist **env_list);
int					exec_external_or_piped_cmd(t_dlist **cmd_list,
						t_dlist **env_list);
// exec_test.c
void				print_arr_str(char **arr_str);
void				print_cmd_list(t_dlist **cmd_list);
// find_cmd_path.c
char				**get_paths(t_dlist **env_list);
char				*cat_path(char *path, char *cmd);
char				*find_cmd_path(char *paths[], char *cmd);
// forked_process_manage.c
void				child_process(t_dlist *current, t_dlist **env_list);
void				close_parent_pipe(t_dlist *current);
void				fail_fork(void);
int					wait_children(t_dlist **cmd_list);
// heredoc.c
void				input_heredocs(t_cmd *cmd, t_dlist **env_list);
int					get_delimiter_type(char *delimiter);
char				*expand_heredoc(char *str, t_dlist **env_list);
void				input_hd(t_cmd *cmd, t_redir *redir, int fd,
						t_dlist **env_list);
void				ft_heredoc(t_cmd *cmd, t_redir *redir, t_dlist **env_list);
// set_pipe_fork.c
void				set_pipe_if_needed(t_dlist *current);
void				set_fork(t_dlist *current);
// set_tmp_file.c
void				set_tmpfile_name(t_cmd *cmd, size_t cmd_idx);
char				*generate_tmpfile_name(size_t cmd_idx, size_t redir_idx);
void				delete_tmp_files(t_cmd *cmd);
// store_stdio.c
void				store_stdio(t_dlist *current);
void				restore_stdio(t_dlist *current);
// utils.c
int					ft_close(int fd);
void				ft_pipe(int fd[2]);
int					delete_file(const char *filepath);
int					file_open(char *file, int flag, int mode);
void				free_strarr(char **arr);

#endif