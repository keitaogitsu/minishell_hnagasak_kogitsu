/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 14:40:15 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/04 13:35:06 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_tokens(t_token *tokens)
{

	while (tokens != NULL)
	{
		printf("token: %s\n", tokens->str);
		tokens = tokens->next;
	}
}

void	mainloop(char *line)
{
	t_token *tokens;
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
		print_tokens(tokens);
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
