/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:00:02 by hnagasak          #+#    #+#             */
/*   Updated: 2024/04/04 05:44:49 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handlers.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void	sigint_handler_in_heredoc(int signum)
{
	(void)signum;
	g_signum = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

int	eof_handler_in_heredoc(void)
{
	write(STDOUT_FILENO, "\033[A\033[2K\r> ", 10);
	return (1);
}

void	sigint_handler_in_exec(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
}

void	sigquit_handler_in_exec(int signum)
{
	(void)signum;
	printf("Quit: %d\n", SIGQUIT);
}
