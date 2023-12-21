/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:55:27 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/19 17:56:02 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*replace_tilde(const char *str)
{
	const char	*replacement = "/Users/hiroya/";

	if (str[0] != '~')
		return (strdup(str));
	return (ft_strjoin(replacement, str + 1));
}

void	ft_cd(char *argv[])
{
	char	*path;

	// printf("--- ft_cd ---\n");
	if (argv[1] == NULL)
		path = replace_tilde("~");
	else
		path = replace_tilde(argv[1]);
	if (chdir(path))
		printf("minishell: cd: %s:%s\n", argv[1], strerror(errno));
	// printf("pwd:%s\n", getcwd(NULL, 0));
	free(path);
}

void	ft_pwd(void)
{
	char	*path;

	// printf("--- ft_pwd ---\n");
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}
