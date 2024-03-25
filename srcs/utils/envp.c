/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 01:45:42 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/20 04:36:44 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "utils.h"

// envpからkeyとvalueを取得する
// TODO: 先頭が=の場合にどうするか？
void	get_key_value(char *envp, char **key, char **value)
{
	char	*delimiter;

	delimiter = ft_strchr(envp, '=');
	if (delimiter == NULL)
	{
		*key = NULL;
		*value = NULL;
		return ;
	}
	*key = ft_substr(envp, 0, delimiter - envp);
	*value = ft_strdup(delimiter + 1);
}

// convert env_list to char**
char	**envlist2arr(t_dlist **env_list)
{
	char	**envp;
	t_dlist	*current;
	t_env	*env;
	size_t	i;

	i = 0;
	current = *env_list;
	envp = (char **)malloc(sizeof(char *) * (ft_dlstsize(env_list) + 1));
	if (!envp)
		malloc_error_exit();
	while (current != NULL)
	{
		env = (t_env *)current->cont;
		envp[i] = ft_strjoin(env->key, "=");
		if (env->value != NULL)
			envp[i] = ft_strjoin(envp[i], env->value);
		current = current->nxt;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

size_t	get_argc(char *argv[])
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	is_env_key_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
