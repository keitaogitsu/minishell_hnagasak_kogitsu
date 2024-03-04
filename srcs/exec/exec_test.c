/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:37:10 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/05 00:34:36 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
