/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 22:02:46 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/06 22:03:45 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

// 外部コマンドのパスを探し、コマンド名を連結して返す
// paths: PATHを:で分割した文字列配列
// cmd: 検索するコマンド名
char	*find_cmd_path(char *paths[], char *cmd)
{
	int		i;
	char	*cmd_path;

	if (ft_strchr(cmd, '/') != NULL || paths == NULL)
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
