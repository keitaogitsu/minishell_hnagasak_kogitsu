/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/28 22:07:16 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "debug.h"
#include "exec.h"
#include "expander.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
#include "free.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>

int	shell_exit(char *line)
{
	free(line);
	printf("\033[A\033[2K\rminishell > exit\n");
	return (1);
}

int	newline_process(char *line)
{
	free(line);
	return (1);
}

void	mainloop(char *line, t_dlist **env_list)
{
	t_token	*tokens;
	t_dlist	**cmd_list;

	while (1)
	{
		line = readline("minishell > ");
		if (line == NULL && shell_exit(line))
			break ;
		else if (ft_strlen(line) == 0 && newline_process(line))
			continue ;
		add_history(line);
		tokens = tokenize(line);
		free(line);
		// ft_debug("--- after tokenize ---\n");
		// print_tokens(tokens);
		if (!is_cmd_line(tokens))
		{
			ft_errmsg("syntax error\n");
			continue ;
		}
		tokens = expand_env(tokens, env_list);
		// ft_debug("--- after expand_env ---\n");
		// print_tokens(tokens);
		cmd_list = create_cmd_list(tokens, env_list);
		// ft_debug("--- after create_cmd_list ---\n");
		// print_cmd_list(cmd_list);
		exec_cmd_list(cmd_list, env_list);
		free_tokens(tokens);
		free_cmd_list(cmd_list);
	}
}

void	signal_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_dlist	**env_list;
	char	*line;

	(void)argc;
	(void)argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	line = NULL;
	env_list = init_env(envp);
	mainloop(line, env_list);
	free_envlist(env_list);
	return (0);
}
