/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 01:45:42 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/29 17:45:37 by hnagasak         ###   ########.fr       */
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

// calcule the number of envp
size_t	count_envp(char **envp)
{
	size_t	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

size_t	get_argc(char *argv[])
{
	size_t	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
