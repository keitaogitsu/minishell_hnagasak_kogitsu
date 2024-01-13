/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:20:30 by kogitsu           #+#    #+#             */
/*   Updated: 2024/01/13 15:48:04 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


size_t get_argv_len(t_token *token)
{
	size_t len;
	len = 0;
	while(token != NULL && token->type != CHAR_PIPE)
	{
		printf("str:%s\n",token->str);
		len++;
		token = token->next;
	}
	printf("len:%zu\n",len);
	return (len);
}

t_dlist	**create_cmd_list(t_token *tokens)
{
	t_dlist	**cmd_list;
	t_cmd	*cmd;
	size_t	i;

	cmd_list = (t_dlist **)malloc(sizeof(t_dlist *));
	while (tokens != NULL)
	{
		printf("1.tokens->str: %s\n", tokens->str);
		i = 0;
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		printf("cmd:%p\n",cmd);
		cmd->argv = (char **) malloc(sizeof(char *) * (get_argv_len(tokens) + 1) );
		while (tokens != NULL && tokens->type != CHAR_PIPE)
		{
			printf("2.tokens->str: %s\n", tokens->str);
			
			if (tokens->type == CHAR_GENERAL)
			{
				printf("3.tokens->str: %s\n", tokens->str);
				cmd->argv[i] = tokens->str;
				printf("cmd->argv[%zu]: %s\n", i,cmd->argv[i]);
				i++;
			}
			tokens = tokens->next;
		}
		printf("argv[0]:%s\n",cmd->argv[0]);
		printf("argv[1]:%s\n",cmd->argv[1]);
		*cmd_list = ft_dlstnew(cmd);
		tokens = tokens->next;
	}
	return (cmd_list);
}
