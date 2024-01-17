/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/15 05:46:04 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "lexer.h"
#include "utils.h"
#include "debug.h"
#include <errno.h>
#include <stdio.h>

void print_arr_str(char **arr_str){
	printf("--- print arr_str ---\n");
	while(*arr_str != NULL)
	{
		printf("arr_str: (%s)\n", *arr_str);
		arr_str++;
	}
}

// generate t_dlist of t_cmd for test
t_dlist	**test_cmd_list(char **str_cmds, t_dlist **envlst)
{
	int		i;
	int		n;
	t_dlist **cmd_list;
	t_cmd	*cmd;
	// char	**str_cmds;

	print_arr_str(str_cmds);

	cmd_list = (t_dlist**) malloc(sizeof(t_dlist *));
	n = 1;
	i = 0;
	while (str_cmds[i] != NULL)
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		cmd->argv = ft_split(str_cmds[i],' ');
		cmd->envp = envlst;
		ft_dlstnew(cmd);
		ft_dlstadd_back(cmd_list, ft_dlstnew(cmd));
		i++;
	}
	return (cmd_list);
}

void print_cmd_list(t_dlist **cmd_list)
{
	t_dlist *current;
	t_cmd	*cmd;
	int		i;

	current = *cmd_list;
	printf("--- print_cmd_list ---\n");
	while (current)
	{
		
		cmd = current->cont;
		i = 0;
		printf("%s: ", cmd->argv[0]);
		while (cmd->argv[i] != NULL)
		{
			printf("%s ",cmd->argv[i]);
			i++;
		}
		printf("\n");
		current = current->nxt;
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
		// test_builtin(ft_split(line, ' '), env_list);
		cmd_list = test_cmd_list(ft_split(line,'|'),env_list);
		print_cmd_list(cmd_list);
		exec_cmd_list(cmd_list, env_list);
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
