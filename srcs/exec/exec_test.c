/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:37:10 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/20 06:40:50 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		cmd->pipe[0] = -1;
		cmd->pipe[1] = -1;
		ft_dlstnew(cmd);
		ft_dlstadd_back(cmd_list, ft_dlstnew(cmd));
		i++;
	}
	return (cmd_list);
}

void print_arr_str(char **arr_str){
	ft_debug("--- print arr_str ---\n");
	while(*arr_str != NULL)
	{
		ft_debug("arr_str: (%s)\n", *arr_str);
		arr_str++;
	}
}



void print_cmd_list(t_dlist **cmd_list)
{
	t_dlist *current;
	t_cmd	*cmd;
	int		i;

	current = *cmd_list;
	ft_debug("--- print_cmd_list ---\n");
	while (current)
	{
		
		cmd = current->cont;
		i = 0;
		ft_debug("%s: ", cmd->argv[0]);
		while (cmd->argv[i] != NULL)
		{
			ft_debug("%s ",cmd->argv[i]);
			i++;
		}
		ft_debug("\n");
		t_dlist *lst = cmd->input;
		while(lst != NULL )
		{
			t_redir *redir = (t_redir *)lst->cont;
			ft_debug("input > file:%s type:%d\n",redir->file,redir->type);
			lst = lst->nxt;
		}
		lst = cmd->output;
		while (lst != NULL)
		{
			t_redir *redir = (t_redir *)lst->cont;
			ft_debug("output > file:%s type:%d\n",redir->file,redir->type);
			lst = lst->nxt;
		}
		current = current->nxt;
	}
}