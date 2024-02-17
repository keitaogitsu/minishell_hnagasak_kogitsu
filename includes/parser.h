/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:21:28 by kogitsu           #+#    #+#             */
/*   Updated: 2024/02/17 12:29:25 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "utils.h"
# include "lexer.h"
# include "exec.h"

size_t  get_argv_len(t_token *token);
t_redir *crt_redir(char *file, t_redir_type type);
t_cmd   *cmd_init(t_token *tokens, t_dlist **env_list);
void    cmd_output_join(t_cmd *cmd, t_redir *redir);
t_dlist **create_cmd_list(t_token *tokens, t_dlist **env_list);

#endif