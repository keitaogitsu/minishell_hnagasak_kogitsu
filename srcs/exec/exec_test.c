/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:37:10 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/17 21:20:41 by kogitsu          ###   ########.fr       */
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
	printf("--- print arr_str ---\n");
	while(*arr_str != NULL)
	{
		printf("arr_str: (%s)\n", *arr_str);
		arr_str++;
	}
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
		t_dlist *lst = cmd->input;
		while(lst != NULL )
		{
			t_redir *redir = (t_redir *)lst->cont;
			printf("input> file:%s type:%d\n",redir->file,redir->type);
			lst = lst->nxt;
		}
		lst = cmd->output;
		while (lst != NULL)
		{
			t_redir *redir = (t_redir *)lst->cont;
			printf("output> file:%s type:%d\n",redir->file,redir->type);
			lst = lst->nxt;
		}
		current = current->nxt;
	}
}