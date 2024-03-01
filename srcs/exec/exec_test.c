/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:37:10 by hnagasak          #+#    #+#             */
/*   Updated: 2024/02/29 19:00:48 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// generate t_dlist of t_cmd for test
// t_dlist	**test_cmd_list(char **str_cmds, t_dlist **envlst)
// {
// 	int		i;
// 	int		n;
// 	t_dlist **cmd_list;
// 	t_cmd	*cmd;
// 	// char	**str_cmds;

// 	print_arr_str(str_cmds);

// 	cmd_list = (t_dlist**) malloc(sizeof(t_dlist *));
// 	n = 1;
// 	i = 0;
// 	while (str_cmds[i] != NULL)
// 	{
// 		cmd = (t_cmd *)malloc(sizeof(t_cmd));
// 		cmd->argv = ft_split(str_cmds[i],' ');
// 		cmd->envp = envlst;
// 		cmd->pipe[0] = -1;
// 		cmd->pipe[1] = -1;
// 		ft_dlstnew(cmd);
// 		ft_dlstadd_back(cmd_list, ft_dlstnew(cmd));
// 		i++;
// 	}
// 	return (cmd_list);
// }

void	print_arr_str(char **arr_str)
{
	ft_debug("--- print arr_str ---\n");
	while (*arr_str != NULL)
	{
		ft_debug("arr_str: (%s)\n", *arr_str);
		arr_str++;
	}
}

void	print_redirects(char *str, t_dlist *lst)
{
	t_redir	*redir;

	ft_debug("--- print_redirects ---\n");
	while (lst != NULL)
	{
		redir = (t_redir *)lst->cont;
		ft_debug("%s > file: %s, type: %d\n", str, redir->file, redir->type);
		lst = lst->nxt;
	}
}

void	print_cmd_list(t_dlist **cmd_list)
{
	t_dlist	*current;
	t_cmd	*cmd;
	int		i;

	current = *cmd_list;
	while (current)
	{
		cmd = current->cont;
		i = 0;
		ft_debug("[print_cmd_list] argv: ");
		while (cmd->argv[i] != NULL)
		{
			ft_debug("%d:%s ", i, cmd->argv[i]);
			i++;
		}
		ft_debug("\n");
		print_redirects("input", cmd->input);
		print_redirects("output", cmd->output);
		current = current->nxt;
	}
}
