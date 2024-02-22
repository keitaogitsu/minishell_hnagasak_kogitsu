/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 01:45:42 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/20 08:33:00 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "utils.h"

// TODO: 先頭が=の場合にどうするか？
static void	get_key_value(char *envp, char **key, char **value)
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

void	update_env_value(t_dlist **env_list, char *envp)
{
	t_dlist	*current;
	t_env	*env;
	char	*key;
	char	*value;

	current = *env_list;
	get_key_value(envp, &key, &value);
	if (key == NULL)
		return ;
	while (current)
	{
		env = (t_env *)current->cont;
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
		{
			free(env->value);
			if (value != NULL)
				env->value = value;
			else
				env->value = ft_strdup("");
			free(key);
			return ;
		}
		current = current->nxt;
	}
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
	if (!env)
	{
		free(key);
		free(value);
		return (NULL);
	}
	env->key = key;
	if (value != NULL)
		env->value = value;
	else
		env->value = ft_strdup("");
	env->is_shell_var = is_shell_var;
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
	ft_debug("--- init_env ---\n");
	env_list = (t_dlist **)malloc(sizeof(t_dlist *));
	while (envp[i] && i < 50)
	{
		if (i == 0)
			*env_list = ft_dlstnew(to_env(envp[i], 0));
		else
			ft_dlstadd_back(env_list, ft_dlstnew(to_env(envp[i], 0)));
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
	return (i);
}

char	**envlist2arr(t_dlist **env_list)
{
	char	**envp;
	t_dlist	*current;
	t_env	*env;
	size_t	i;

	ft_debug("--- envlist2arr ---\n");
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
	t_dlist *tmp;
	t_dlist *current;
	t_env *env;

	current = *envlist;
	while (current != NULL)
	{
		tmp = current;
		env = (t_env *)tmp->cont;
		ft_debug("---free_envlist [%s]---\n", env->key);
		// ft_debug("env->key:%s\n", env->key);
		// ft_debug("env->value:%s\n", env->value);
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