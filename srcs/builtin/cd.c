/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:55:27 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/11 10:23:43 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "free.h"

// if 1st char is '~', replace it with $HOME
char	*replace_tilde(const char *str, t_dlist **env_list)
{
	t_env	*env;
	char	*home;

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

	env = find_existing_env("PWD", env_list);
	if (env == NULL)
		pwd = ft_strdup("");
	else
		pwd = env->value;
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	update_env_value(env_list, oldpwd);
	ft_free(oldpwd);
}

static void	cd_errmsg(char **argv)
{
	ft_errmsg("minishell: cd: ");
	ft_errmsg(argv[1]);
	ft_errmsg(": ");
	ft_errmsg(strerror(errno));
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
		cd_errmsg(argv);
	free(path);
}
