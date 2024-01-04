/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:10:26 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/02 19:21:58 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "lexer.h"
#include "utils.h"
#include <stdio.h>
#include <errno.h>

void	test_is_builtin(char **argv, t_dlist **env_list)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->argv = argv;
	if (is_builtin_cmd(cmd))
		printf("OK: builtin command\n");
	else
		printf("NG: not builtin!!\n");
}

void	test_builtin(char **argv, t_dlist **env_list)
{
	// if (ft_strncmp(argv[0], "echo", 4) == 0)
	// 	ft_echo(argv);
	// else if (ft_strncmp(argv[0], "cd", 2) == 0)
	// 	ft_cd(argv);
	// else if (ft_strncmp(argv[0], "pwd", 3) == 0)
	// 	ft_pwd();
	// else if (ft_strncmp(argv[0], "exit", 4) == 0)
	// 	ft_exit(argv);
	// else if (ft_strncmp(argv[0], "env", 3) == 0)
	// 	ft_env(argv, env_list);
	// else if (ft_strncmp(argv[0], "export", 6) == 0)
	// 	ft_export(argv, env_list);
	// else if (ft_strncmp(argv[0], "unset", 5) == 0)
	// 	ft_unset(argv, env_list);
	// // else if (ft_strncmp(argv[0], "ls", 2) == 0)
	// // 	ft_execmd(argv, env_list);
	// // else
	// // 	printf("command not found!!\n");
	// else
	test_is_builtin(argv, env_list);
}

// generate t_dlist of t_cmd for test
t_dlist	**gen_cmd_list(char **argv, t_dlist **envlst)
{
	int		i;
	int		n;
	t_dlist **cmd_list;
	t_cmd	cmd;
	char	**str_cmds;

	str_cmds = ft_split("echo Hello ,echo World", ',');
	cmd_list = (t_dlist**) malloc(sizeof(t_dlist *)); 
	n = 1;
	i = 0;
	while (i < n)
	{
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		cmd->argv = str_cmds[i];
		cmd->envp = *envlst;
		*cmd_list = (t_dlist *) malloc(sizeof(t_dlist));
		(*cmd_list)->cont = 
	}
}

void	mainloop(char *line, t_dlist **env_list)
{
	t_list	*tokens;
	t_dlist **cmd_list;

	while (1)
	{
		line = readline("minishell > ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break ;
		}
		// test_builtin(ft_split(line, ' '), env_list);
		cmd_list = gen_cmd_list(argv,env_list);
		add_history(line);
		// tokens = tokenize(line);
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
