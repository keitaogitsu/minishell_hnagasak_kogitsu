/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:02:46 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/28 09:32:32 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "exit_status.h"
#include "free.h"

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

char	**get_paths(t_dlist **env_list)
{
	t_env	*env;
	char	**paths;
	char	*path;

	path = NULL;
	env = find_existing_env("PATH", env_list);
	if (env != NULL)
		path = ft_strdup(env->value);
	paths = ft_split(path, ':');
	free(path);
	return (paths);
}

// int	errmsg_isdir(char *cmd)
// {
// 	ft_errmsg("minishell: ");
// 	ft_errmsg(cmd);
// 	ft_errmsg(": is a directory\n");
// 	return (STATUS_EISDIR);
// }

// int	errmsg_missing_path(char *cmd)
// {
// 	ft_errmsg("minishell: ");
// 	ft_errmsg(cmd);
// 	ft_errmsg(": No such file or directory\n");
// 	return (STATUS_ENOENT);
// }

// int	errmsg_permission(char *cmd)
// {
// 	ft_errmsg("minishell: ");
// 	ft_errmsg(cmd);
// 	ft_errmsg(": Permission denied\n");
// 	return (STATUS_EACCES);
// }

// int	errmsg_cmd_not_found(char *cmd)
// {
// 	ft_errmsg("minishell: ");
// 	ft_errmsg(cmd);
// 	ft_errmsg(": command not found\n");
// 	return (STATUS_CMD_NOT_FOUND);
// }

int	find_cmd_path(char **cmd_path, char *paths[], char *cmd)
{
	int	i;

	if (ft_strchr(cmd, '/') != NULL || paths == NULL)
	{
		if (is_directory(cmd))
			return (errmsg_isdir(cmd));
		if (access(cmd, F_OK) != 0)
			return (errmsg_missing_path(cmd));
		if (access(cmd, X_OK) != 0)
			return (errmsg_permission(cmd));
		*cmd_path = ft_strdup(cmd);
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (paths[i] != NULL)
	{
		*cmd_path = cat_path(paths[i], cmd);
		if (access(*cmd_path, X_OK) == 0)
			return (EXIT_SUCCESS);
		*cmd_path = ft_free(*cmd_path);
		i++;
	}
	return (errmsg_cmd_not_found(cmd));
}
