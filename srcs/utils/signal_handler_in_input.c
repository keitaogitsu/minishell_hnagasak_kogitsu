/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_in_input.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:15:09 by kogitsu           #+#    #+#             */
/*   Updated: 2024/04/07 23:22:22 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handlers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// Error if included before stdio.h
#include <readline/readline.h>

void	sigint_handler_in_input(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	eof_handler_in_input(char *line)
{
	free(line);
	printf("\033[A\033[2K\rminishell > exit\n");
	return (1);
}
