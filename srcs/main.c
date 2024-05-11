/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2024/04/07 23:24:02 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "debug.h"
#include "exec.h"
#include "expander.h"
#include "free.h"
#include "lexer.h"
#include "parser.h"
#include "signal_handlers.h"
#include "utils.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>

int			g_signum = 0;

static void	set_signal_handler(void)
{
	signal(SIGINT, sigint_handler_in_input);
	signal(SIGQUIT, SIG_IGN);
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
	int		exit_status;

	exit_status = 0;
	while (1)
	{
		set_signal_handler();
		line = readline("minishell > ");
		if (line == NULL && eof_handler_in_input(line))
			break ;
		else if (ft_strlen(line) == 0 && newline_process(line))
			continue ;
		add_history(line);
		tokens = tokenize(line);
		free(line);
		if (!is_cmd_line(tokens))
			continue ;
		tokens = expand_env(tokens, env_list, exit_status);
		cmd_list = create_cmd_list(tokens, env_list);
		print_cmd_list(cmd_list);
		exec_cmd_list(cmd_list, env_list, &exit_status);
		free_tokens(tokens);
		free_cmd_list(cmd_list);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_dlist	**env_list;
	char	*line;

	(void)argc;
	(void)argv;
	line = NULL;
	env_list = init_env(envp);
	mainloop(line, env_list);
	free_envlist(env_list);
	return (0);
}
