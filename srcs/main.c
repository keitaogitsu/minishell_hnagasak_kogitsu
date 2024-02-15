/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/16 07:45:47 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "exec.h"
#include "lexer.h"
#include "utils.h"
#include "debug.h"
#include "parser.h"
#include "expander.h"
#include <errno.h>
#include <stdio.h>

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens != NULL)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void free_envlist(t_dlist **envlist)
{
	t_dlist	*tmp;
	t_dlist	*current;
	t_env *env;

	current = *envlist;
	while (current != NULL)
	{
		tmp = current;
		env = (t_env *)tmp->cont;
		printf("---free_envlist [%s]---\n",env->key);
		// printf("env->key:%s\n", env->key);
		// printf("env->value:%s\n", env->value);
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
		add_history(line);
		tokens = tokenize(line);
		free(line);
		if(is_cmd_line(tokens))
			printf("## is command line\n");
		else
			printf("## is NOT command line\n");
		tokens = expand_env(tokens, env_list);
		print_tokens(tokens);
		
		cmd_list = create_cmd_list(tokens, env_list);
		// コマンド実行
		exec_cmd_list(cmd_list, env_list);
		// print_cmd_list(cmd_list);
		free_tokens(tokens);
		break;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_dlist	**env_list;
	char	*line;

	printf("--- main %d---\n",dup(STDIN_FILENO));

	line = NULL;
	env_list = init_env(envp);
	// print_envlist(env_list);
	mainloop(line, env_list);
	free_envlist(env_list);
	return (0);
}
