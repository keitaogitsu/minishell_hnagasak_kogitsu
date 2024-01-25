/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/20 16:35:18 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "lexer.h"
#include "utils.h"
#include "debug.h"
#include "parser.h"
#include <errno.h>
#include <stdio.h>

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
		// cmd_list = gen_cmd_list(ft_split(line,"|"),env_list);
		add_history(line);
		tokens = tokenize(line);
		print_tokens(tokens);
		if(is_cmd_line(tokens))
			printf("## is command line\n");
		else
			printf("## is NOT command line\n");
		// cmd_list = create_cmd_list(tokens, env_list);
		// print_cmd_list(cmd_list);
		// free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_dlist	**env_list;
	char	*line;

	printf("--- main %d---\n",dup(STDIN_FILENO));

	line = NULL;
	env_list = init_env(envp);
	// print_env(*env_list);
	mainloop(line, env_list);
	// printf("exit\n");
	return (0);
}
