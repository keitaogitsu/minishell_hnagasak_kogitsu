/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:55:27 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/11 09:55:55 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "free.h"

// char	*get_env_value(char *key, t_dlist **env_list)
// {
// 	t_dlist	*current;
// 	t_env	*env;

// 	current = *env_list;
// 	while (current)
// 	{
// 		env = current->cont;
// 		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
// 			return (env->value);
// 		current = current->nxt;
// 	}
// 	return (NULL);
// }

// if 1st char is '~', replace it with $HOME
char	*replace_tilde(const char *str, t_dlist **env_list)
{
	t_env	*env;
	char	*home;

	// home = get_env_value("HOME", env_list);
	home = NULL;
	env = find_existing_env("HOME", env_list);
	if (env != NULL)
		home = env->value;
	if (str[0] != '~')
		return (strdup(str));
	return (ft_strjoin(home, str + 1));
}

void	update_oldpwd(t_dlist **env_list)
{
	t_env	*env;
	char	*pwd;
	char	*oldpwd;

	// PWDを検索
	env = find_existing_env("PWD", env_list);
	if (env == NULL)
		pwd = ft_strdup("");
	else
		pwd = env->value;
	// OLDPWDの更新
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	update_env_value(env_list, oldpwd);
	ft_free(oldpwd);
}

void	ft_cd(char *argv[], t_dlist **env_list)
{
	char	*path;
	char	*cwd;
	char	*str_env;

	if (argv[1] == NULL)
		path = replace_tilde("~", env_list);
	else
		path = replace_tilde(argv[1], env_list);
	update_oldpwd(env_list);
	if (chdir(path) == 0)
	{
		cwd = ft_malloc(sizeof(char) * 1024);
		getcwd(cwd, sizeof(char) * 1024);
		if (cwd != NULL)
		{
			str_env = ft_strjoin("PWD=", cwd);
			update_env_value(env_list, str_env);
			ft_free(str_env);
		}
		cwd = ft_free(cwd);
	}
	else
	{
		ft_errmsg("minishell: cd: ");
		ft_errmsg(argv[1]);
		ft_errmsg(": ");
		ft_errmsg(strerror(errno));
	}
	free(path);
}
