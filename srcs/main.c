/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/04 17:56:05 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "lexer.h"
#include "utils.h"
#include <errno.h>
#include <stdio.h>

// generate t_dlist of t_cmd for test
// t_dlist	**gen_cmd_list(char **argv, t_dlist **envlst)
// {
// 	int		i;
// 	int		n;
// 	t_dlist **cmd_list;
// 	t_cmd	*cmd;
// 	char	**str_cmds;

// 	str_cmds = ft_split("echo Hello ,echo World", ',');
// 	cmd_list = (t_dlist**) malloc(sizeof(t_dlist *));
// 	n = 1;
// 	i = 0;
// 	while (i < n)
// 	{
// 		cmd = (t_cmd *)malloc(sizeof(t_cmd));
// 		cmd->argv = str_cmds[i];
// 		cmd->envp = *envlst;
// 		*cmd_list = (t_dlist *) malloc(sizeof(t_dlist));
// 		(*cmd_list)->content = cmd;
// 		(*cmd_list)->next = NULL;
// 	}
// }

void	print_tokens(t_token *tokens)
{
	while (tokens != NULL)
	{
		printf("token: %s type:%d\n", tokens->str, tokens->type);
		tokens = tokens->next;
	}
}

void	mainloop(char *line, t_dlist **env_list)
{
	t_token	*tokens;
	t_dlist	**cmd_list;

	while (1)
	{
		line = readline("minishell > ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break ;
		}
		test_builtin(ft_split(line, ' '), env_list);
		// cmd_list = gen_cmd_list(ft_split(line,"|"),env_list);
		add_history(line);
		// tokens = tokenize(line);
		// print_tokens(tokens);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_dlist	**env_list;
	char	*line;

	line = NULL;
	env_list = init_env(envp);
	// print_env(*env_list);
	mainloop(line, env_list);
	// printf("exit\n");
	return (0);
}
