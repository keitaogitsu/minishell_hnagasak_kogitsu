/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path_errmsg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:02:46 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/28 09:36:18 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exit_status.h"

int	errmsg_isdir(char *cmd)
{
	ft_errmsg("minishell: ");
	ft_errmsg(cmd);
	ft_errmsg(": is a directory\n");
	return (STATUS_EISDIR);
}

int	errmsg_missing_path(char *cmd)
{
	ft_errmsg("minishell: ");
	ft_errmsg(cmd);
	ft_errmsg(": No such file or directory\n");
	return (STATUS_ENOENT);
}

int	errmsg_permission(char *cmd)
{
	ft_errmsg("minishell: ");
	ft_errmsg(cmd);
	ft_errmsg(": Permission denied\n");
	return (STATUS_EACCES);
}

int	errmsg_cmd_not_found(char *cmd)
{
	ft_errmsg("minishell: ");
	ft_errmsg(cmd);
	ft_errmsg(": command not found\n");
	return (STATUS_CMD_NOT_FOUND);
}
