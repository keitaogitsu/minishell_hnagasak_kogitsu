/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/17 15:21:42 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	mainloop(char *line)
{
	t_list *tokens;
	while (1)
	{
		line = readline("minishell > ");
		if (line == NULL || strlen(line) == 0)
		{
			free(line);
			break;
		}
		add_history(line);
		tokens = tokenize(line);
		// for (int i = 0; tokens[i] != NULL ; i++)
		// 	printf("tokens %s\n",tokens[i]);
		free(line);
	}
}

int main(void)
{
	char *line = NULL;

	mainloop(line);
	printf("exit\n");
	return (0);
}
