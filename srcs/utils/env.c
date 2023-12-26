/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 01:45:42 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/27 03:03:10 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/**
 * @brief Create a new t_env object from a given string.
 *
 * This function takes an environment variable represented as a string (envp),
 * splits it into key and value using '=' as a delimiter, and then creates a
 * new t_env object with these key and value. The object also stores whether
 * it is a shell variable or not, based on the is_shell_var parameter.
 *

	* @param envp A string representing the environment variable in the format "KEY=VALUE".

	* @param is_shell_var An integer indicating if the variable is a shell variable (non-zero value)
 *         or not (zero value).

	* @return t_env* A pointer to the newly created t_env object. Returns NULL if the allocation fails.
 */
t_env	*to_env(char *envp, int is_shell_var)
{
	t_env	*env;
	char	**tmp;

	tmp = ft_split(envp, '=');
	// printf("##1 %s: %p\n", tmp[0],tmp[1]);
	if (!tmp || !tmp[0])
	{
		free(tmp);
		return (NULL);
	}
	env = malloc(sizeof(t_env));
	if (!env)
	{
		free(tmp[0]);
		free(tmp[1]);
		free(tmp);
		return (NULL);
	}
	// if(ft_strncmp(tmp[0], "NVM_RC_VERSION", 14) == 0)
	// 	printf("###NVM_RC_VERSION\n");
		// printf("##2 %s: %p\n", tmp[0],tmp[1]);
	env->key = tmp[0];
	if(tmp[1] != NULL)
		env->value = tmp[1];
	else
		env->value = "";
	env->is_shell_var = is_shell_var;
	free(tmp);
	return (env);
}

// calcule the number of envp
size_t	count_envp(char **envp)
{
	size_t	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

t_dlist	**init_env(char **envp)
{
	t_dlist	**env_list;
	t_env	*env;
	int		i;

	i = 0;
	printf("--- init_env ---\n");
	env_list = malloc(sizeof(t_dlist *) * (count_envp(envp) + 1));
	while (envp[i])
	{
		// printf("envp[%d]: %s\n", i, envp[i]);
		if (i == 0)
			ft_dlstnew(to_env(envp[i], 0));
		else
			ft_dlstadd_back(env_list, ft_dlstnew(to_env(envp[i], 0)));
		i++;
	}
	return (env_list);
}
