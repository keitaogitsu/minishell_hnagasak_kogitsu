/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 04:11:28 by hnagasak          #+#    #+#             */
/*   Updated: 2024/04/07 23:18:40 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HANDLERS_H
# define SIGNAL_HANDLERS_H

extern int	g_signum;

// srcs/utils/signal_handler_in_input.c
void		sigint_handler_in_input(int signum);
int			eof_handler_in_input(char *line);
// srcs/exec/signal_handlers.c
void		sigint_handler_in_heredoc(int signum);
int			eof_handler_in_heredoc(void);
void		sigint_handler_in_exec(int signum);
void		sigquit_handler_in_exec(int signum);

#endif