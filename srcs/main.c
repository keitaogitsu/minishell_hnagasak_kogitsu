/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/17 15:11:32 by kogitsu          ###   ########.fr       */
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

void	free_redir(t_dlist *redir_list)
{
	t_redir	*redir;
	t_dlist	*tmp;

	while (redir_list != NULL)
	{
		tmp = redir_list;
		redir = (t_redir *)redir_list->cont;
		free(redir->file);
		redir->file = NULL;
		free(redir);
		redir_list->cont = NULL;
		redir_list = redir_list->nxt;
		free(tmp);
		tmp = NULL;
	}
}

void	free_cmdlist(t_dlist **cmd_list)
{
	t_dlist	*tmp;
	t_dlist	*current;
	t_cmd	*cmd;
	size_t	argc;
	size_t	i;

	current = *cmd_list;
	while (current != NULL)
	{
		tmp = current;
		cmd = (t_cmd *)tmp->cont;
		argc = get_argc(cmd->argv);
		i = 0;
		while (i < argc)
		{
			free(cmd->argv[i]);
			cmd->argv[i] = NULL;
			i++;
		}
		free(cmd->argv);
		cmd->argv = NULL;
		if (cmd->path != NULL)
			free(cmd->path);
		cmd->path = NULL;
		free_redir(cmd->input);
		free_redir(cmd->output);
		free(cmd);
		cmd = NULL;
		current = current->nxt;
		free(tmp);
		tmp = NULL;
	}
}

// void print_redir_list(t_dlist *redir_list)
// {
// 	t_dlist	*current;
// 	t_redir	*redir;

// 	current = redir_list;
// 	while(current != NULL)
// 	{
// 		redir = (t_redir *)current->cont;
// 		printf("redir[%s]  ", current->i);
// 		printf("redir->file:%s ", redir->file);
// 		printf("redir->type:%d\n", redir->type);
// 		redir_list = redir_list->nxt;
// 	}
// }

// void print_cmd_list(t_dlist **cmd_list)
// {
// 	t_dlist	*current;
// 	t_cmd	*cmd;	
	
// 	current = *cmd_list;
// 	while(current != NULL)
// 	{
// 		cmd = (t_cmd *)current->cont;
// 		printf("cmd->path:%s\n", cmd->path);
// 		printf("cmd->argc:%zu\n", get_argc(cmd->argv));
// 		size_t i = 0;
// 		while(i < get_argc(cmd->argv))
// 		{
// 			printf("cmd->argv[%zu]:%s\n", i, cmd->argv[i]);
// 			i++;
// 		}
// 		printf("cmd->input:\n");
// 		print_redir_list(cmd->input);
// 		printf("cmd->output:\n");
// 		print_redir_list(cmd->output);
// 		current = current->nxt;
// 	}
// }

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
		printf("\n----- in mainloop -----\n");
		print_tokens(tokens);
		printf("\n------- end in mainloop --------\n");
		cmd_list = create_cmd_list(tokens, env_list);
		print_cmd_list(cmd_list);
		// コマンド実行
		exec_cmd_list(cmd_list, env_list);
		// print_cmd_list(cmd_list);
		free_tokens(tokens);
		// free_cmdlist(cmd_list);
		// break ;
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
