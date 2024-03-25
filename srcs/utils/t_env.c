/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 01:45:42 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/20 04:38:40 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "utils.h"

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
	*env_list = NULL;
	while (envp[i] != NULL)
	{
		ft_dlstadd_back(env_list, ft_dlstnew(to_env(envp[i], !IS_SHELL_VAR)));
		i++;
	}
	return (env_list);
}

// update env_list if the key exists, update the value.
// if the key does not exist, add a new env to the list.
// envp is in the format "KEY=VALUE".
void	update_env_value(t_dlist **env_list, char *envp)
{
	t_env	*env;
	char	*key;
	char	*value;

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

void	remove_env(char *key, t_dlist **env_list)
{
	t_dlist	*current;
	t_env	*env;

	current = *env_list;
	while (current != NULL)
	{
		env = (t_env *)current->cont;
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			if (current->prv != NULL)
				current->prv->nxt = current->nxt;
			if (current->nxt != NULL)
				current->nxt->prv = current->prv;
			if (current == *env_list)
				*env_list = current->nxt;
			free(env->key);
			free(env->value);
			free(env);
			free(current);
			return ;
		}
		current = current->nxt;
	}
}
