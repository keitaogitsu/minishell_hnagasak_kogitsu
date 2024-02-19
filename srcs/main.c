/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/20 08:39:31 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "debug.h"
#include "exec.h"
#include "expander.h"
#include "lexer.h"
#include "parser.h"
#include "utils.h"
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

void	mainloop(char *line, t_dlist **env_list)
{
	t_token	*tokens;
	t_dlist	**cmd_list;

	while (1)
	{
		line = readline("minishell > ");
		if (line == NULL  || strlen(line) == 0)
		{
			free(line);
			if(line == NULL)
				break ;
			else
				continue;
		}
		add_history(line);
		tokens = tokenize(line);
		free(line);
		if (!is_cmd_line(tokens))
		{
			ft_errmsg("syntax error\n");
			continue;
		}
			
		ft_debug("DEBUG: %d\n", DEBUG);
		tokens = expand_env(tokens, env_list);
		print_tokens(tokens);
		cmd_list = create_cmd_list(tokens, env_list);
		print_cmd_list(cmd_list);
		exec_cmd_list(cmd_list, env_list);
		free_tokens(tokens);
		// free_cmdlist(cmd_list); // sefaultするので一旦コメントアウト
		// break ; // 動作確認のため一回だけ実行する
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_dlist	**env_list;
	char	*line;

	line = NULL;
	env_list = init_env(envp);
	mainloop(line, env_list);
	free_envlist(env_list);
	return (0);
}
