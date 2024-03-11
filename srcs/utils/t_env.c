/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 01:45:42 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/10 13:52:27 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "utils.h"

// update env_list if the key exists, update the value.
// if the key does not exist, add a new env to the list.
// envp is in the format "KEY=VALUE".
void	update_env_value(t_dlist **env_list, char *envp)
{
	// t_dlist	*current;
	t_env	*env;
	char	*key;
	char	*value;

	// printf("--- update_env_value [%s]---\n", envp);

	// current = *env_list;
	get_key_value(envp, &key, &value);
	if (key == NULL)
		return ;
	if (value == NULL)
		value = ft_strdup("");
	env = find_existing_env(key, env_list);
	if (env != NULL)
	{
		free(env->value);
		env->value = value;
	}
	else
		ft_dlstadd_back(env_list, ft_dlstnew(to_env(envp, !IS_SHELL_VAR)));
	free(key);
}

/**
 * @brief Create a new t_env object from a given string.
 * @param envp environment variable in string format "KEY=VALUE"
 * @param is_shell_var if the variable is a shell variable (non-zero value)
 * @return t_env* A pointer to created t_env object
 */
t_env	*to_env(char *envp, int is_shell_var)
{
	t_env	*env;
	char	*key;
	char	*value;

	get_key_value(envp, &key, &value);
	if (key == NULL)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (env == NULL)
	{
		free(key);
		free(value);
		malloc_error_exit();
	}
	env->key = key;
	if (value != NULL)
		env->value = value;
	else
		env->value = ft_strdup("");
	env->is_shell_var = is_shell_var;
	return (env);
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
	int		i;

	i = 0;
	ft_debug("--- init_env ---\n");
	env_list = (t_dlist **)malloc(sizeof(t_dlist *));
	if (env_list == NULL)
		malloc_error_exit();
	while (envp[i] != NULL)
	{
		ft_dlstadd_back(env_list, ft_dlstnew(to_env(envp[i], !IS_SHELL_VAR)));
		i++;
	}
	return (env_list);
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

void	free_envlist(t_dlist **envlist)
{
	t_dlist	*tmp;
	t_dlist	*current;
	t_env	*env;

	ft_debug("--- free_envlist ---\n");
	current = *envlist;
	while (current != NULL)
	{
		tmp = current;
		env = (t_env *)tmp->cont;
		free(env->key);
		env->key = NULL;
		free(env->value);
		env->value = NULL;
		free(env);
		env = NULL;
		current = current->nxt;
		free(tmp);
		tmp = NULL;
	}
	free(envlist);
}

/**
 * @brief Find an existing t_env object in the environment list.
 * @param key the key of the environment variable
 * @param env_list double pointer to the head of the double linked list
 * @return t_env* pointer to existing t_env object
 */
t_env	*find_existing_env(char *key, t_dlist **env_list)
{
	t_dlist	*current;
	t_env	*env;

	current = *env_list;
	while (current)
	{
		env = (t_env *)current->cont;
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
			return (env);
		current = current->nxt;
	}
	return (NULL);
}
