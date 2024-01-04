/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:07:35 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/02 16:01:02 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "libft.h"
# include "utils.h"

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
	t_dlist			*envp;
	char			*path;
	t_redir_type	*input;
	t_redir_type	*output;
}					t_cmd;

int	is_builtin_cmd(t_cmd *cmd);

#endif
