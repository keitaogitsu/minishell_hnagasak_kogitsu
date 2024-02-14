/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/11 18:27:59 by kogitsu          ###   ########.fr       */
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
		printf("---free_envlist---\n");
		tmp = current;
		env = (t_env *)tmp->cont;
		printf("env->key:%s\n", env->key);
		printf("env->value:%s\n", env->value);
		free(env->key);
		env->key = NULL;
		free(env->value);
		env->value = NULL;
		free(env);
		env = NULL;
		// free(tmp->prv);
		// tmp->prv = NULL;
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
		// test_builtin(ft_split(line, ' '), env_list);
		// cmd_list = gen_cmd_list(ft_split(line,"|"),env_list);
		add_history(line);
		tokens = tokenize(line);
		free(line);
		if(is_cmd_line(tokens))
			printf("## is command line\n");
		else
			printf("## is NOT command line\n");
		// 変数展開
		tokens = expand_env(tokens, env_list);
		printf("## after expand_env\n");
		printf("toknes_adress:%s\n", tokens->str);
		print_tokens(tokens);
		
		cmd_list = create_cmd_list(tokens, env_list);
		// ここまで使ったt_token：tokensはfreeする
		free_tokens(tokens);
		free_envlist(env_list);
		// コマンド実行
		// exec_cmd_list(cmd_list, env_list);
		// print_cmd_list(cmd_list);
		// free(line);
		break;
	}
}

void print_envlist(t_dlist **env_list)
{
	t_env *env;
	t_dlist *current;

	current = *env_list;
	printf("--- print_env ----\n");
	while (current)
	{
		env = (t_env *) current->cont;
		printf("%s=%s , is_shell_var = %d\n", env->key, env->value,
			env->is_shell_var);
		t_dlist *prev = current->prv;
		t_dlist *next = current->nxt;
		if(prev)
		{
			env = (t_env *) prev->cont;
			printf("prev: %s=%s , is_shell_var = %d\n", env->key, env->value,
				env->is_shell_var);
		}
		if(next)
		{
			env = (t_env *) next->cont;
			printf("next: %s=%s , is_shell_var = %d\n", env->key, env->value,
				env->is_shell_var);
		}
		current = current->nxt;
	}
	printf("--- end print_env ----\n");
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
	return (0);
}
