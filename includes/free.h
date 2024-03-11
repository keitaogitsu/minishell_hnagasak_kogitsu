/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:02:58 by kogitsu           #+#    #+#             */
/*   Updated: 2024/03/11 10:18:52 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "exec.h"
# include "lexer.h"

// free.c
void	free_tokens(t_token *tokens);
void	free_redir(t_dlist *redir_list);
void	*ft_free(void *ptr);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_dlist **cmd_list);
// free2.c
void	free_envlist(t_dlist **envlist);

#endif