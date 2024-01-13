/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:55:27 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/07 09:25:37 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_env_value(char *key, t_dlist **env_list)
{
	t_dlist	*current;
	t_env	*env;

	current = *env_list;
	while (current)
	{
		env = current->cont;
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env->value);
		current = current->nxt;
	}
	return (NULL);
}

char	*replace_tilde(const char *str, t_dlist **env_list)
{
	char		*home;
	const char	*replacement = home;

	// TODO: replace_tilde
	home = get_env_value("HOME", env_list);
	// const char	*replacement = "/Users/hiroya/";
	if (str[0] != '~')
		return (strdup(str));
	return (ft_strjoin(replacement, str + 1));
}

void	ft_cd(char *argv[], t_dlist **env_list)
{
	char	*path;

	// printf("--- ft_cd ---\n");
	if (argv[1] == NULL)
		path = replace_tilde("~", env_list);
	else
		path = replace_tilde(argv[1], env_list);
	if (chdir(path))
		printf("minishell: cd: %s:%s\n", argv[1], strerror(errno));
	// printf("pwd:%s\n", getcwd(NULL, 0));
	free(path);
}
