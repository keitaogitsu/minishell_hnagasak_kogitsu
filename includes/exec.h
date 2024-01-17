/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:07:35 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/13 16:31:28 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "builtin.h"
# include "libft.h"
# include "utils.h"
# include <fcntl.h>

typedef enum e_redir_type
{
	// REDIR_NONE,
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}					t_redir_type;

typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
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
}					t_cmd;

int					is_builtin_cmd(t_cmd *cmd);
void				exec_cmd_list(t_dlist **cmd_list, t_dlist **env_list);

#endif