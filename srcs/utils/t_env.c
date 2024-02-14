/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 01:45:42 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/14 12:47:02 by hnagasak         ###   ########.fr       */
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
	if (tmp[1] != NULL)
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

/**
 * @brief Initializes a double linked list for the environment variables.
 *
 * This function takes the environment variables provided by `envp`
 * and initializes a double linked list, where each node represents
 * an environment variable. The function allocates memory for the
 * list and populates it with the environment variables.
 *
 * @param envp A null-terminated array of strings representing
 *             the environment variables. Each string is in the
 *             format 'KEY=VALUE'.
 *
 * @return Returns a pointer to the head of the double linked list
 *         representing the environment variables. If memory allocation
 *         fails, returns NULL.
 *
 * @note The function uses `malloc` for memory allocation and should
 *       be accompanied by appropriate memory deallocation when the
 *       list is no longer needed.
 * @note This function prints an initialization message to the standard
 *       output. It also contains commented out debugging prints that can
 *       be enabled if needed.
 */
t_dlist	**init_env(char **envp)
{
	t_dlist	**env_list;
	t_env	*env;
	int		i;

	i = 0;
	printf("--- init_env ---\n");
	env_list = (t_dlist **)malloc(sizeof(t_dlist *));
	while (envp[i] && i < 50)
	{
		// printf("envp[%d]: %s\n", i, envp[i]);
		if (i == 0)
			*env_list = ft_dlstnew(to_env(envp[i], 0));
		else
			ft_dlstadd_back(env_list, ft_dlstnew(to_env(envp[i], 0)));
		// printf("#envp[%d]: %s\n", i, envp[i]);
		i++;
	}
	return (env_list);
}

size_t	get_argc(char *argv[])
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;

	// printf("get_argc:%zu\n",i);
	return (i);
}

// convert the list of env to array
// char **list2arr(t_dlist **env_list)
char **envlist2arr(t_dlist **env_list)
{
	char	**envp;
	t_dlist	*current;
	t_env *env;
	size_t	i;

	fprintf(stderr, "--- envlist2arr ---\n");
	i = 0;
	current = *env_list;
	envp = (char **)malloc(sizeof(char *) * (ft_dlstsize(env_list) + 1));
	if (!envp)
		return (NULL);
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