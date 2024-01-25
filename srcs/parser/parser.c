/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:20:30 by kogitsu           #+#    #+#             */
/*   Updated: 2024/01/20 13:58:08 by kogitsu          ###   ########.fr       */
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

t_redir *crt_redir(char *file, t_redir_type type)
{
	t_redir *redir;
	redir = malloc(sizeof(t_redir));
	redir->file = file;
	redir->type = type;
	return (redir);
}

t_dlist	**create_cmd_list(t_token *tokens, t_dlist **env_list)
{
	t_dlist	**cmd_list;
	t_cmd	*cmd;
	t_redir	*redir;
	size_t	i;

	cmd_list = (t_dlist **)malloc(sizeof(t_dlist *));
	while (tokens != NULL)
	{
		// printf("1.tokens->str: %s\n", tokens->str);
		i = 0;
		cmd = (t_cmd *)malloc(sizeof(t_cmd));
		// printf("cmd:%p\n",cmd);
		cmd->argv = (char **) malloc(sizeof(char *) * (get_argv_len(tokens) + 1) );
		cmd->envp = env_list;
		while (tokens != NULL && tokens->type != CHAR_PIPE)
		{
			// printf("2.tokens->str: %s\n", tokens->str);
			if (tokens->type == CHAR_GENERAL)
			{
				// printf("3.tokens->str: %s\n", tokens->str);
				cmd->argv[i] = tokens->str;
				// printf("cmd->argv[%zu]: %s\n", i,cmd->argv[i]);
				i++;
			}
			else if (tokens->type == CHAR_GREATER)
			{
				tokens = tokens->next;
				// printf("4.tokens->str: %s\n", tokens->str);
				// cmd->redirect_out = tokens->next->str;
				redir = crt_redir(tokens->str, REDIR_OUTPUT);
				if (cmd->output == NULL)
					cmd->output = ft_dlstnew(redir);
				else
					ft_dlstadd_back(&cmd->output, ft_dlstnew(redir));
			}
			else if (tokens->type == CHAR_LESSER)
			{
				tokens = tokens->next;
				// printf("5.tokens->str: %s\n", tokens->str);
				redir = crt_redir(tokens->str, REDIR_INPUT);
				if(cmd->input == NULL)
					cmd->input = ft_dlstnew(redir);
				else 	
					ft_dlstadd_back(&cmd->input, ft_dlstnew(redir));
			}
			else if (tokens->type == D_GREATER)
			{
				tokens = tokens->next;
				// printf("6.tokens->str: %s\n", tokens->str);
				redir = crt_redir(tokens->str, REDIR_APPEND);
				if(cmd->output == NULL)
					cmd->output = ft_dlstnew(redir);
				else 	
					ft_dlstadd_back(&cmd->output, ft_dlstnew(redir));
			}
			else if (tokens->type == D_LESSER)
			{
				tokens = tokens->next;
				// printf("7.tokens->str: %s\n", tokens->str);
				redir = crt_redir(tokens->str, REDIR_HEREDOC);
				if(cmd->input == NULL)
					cmd->input = ft_dlstnew(redir);
				else 	
					ft_dlstadd_back(&cmd->input, ft_dlstnew(redir));
			}
			tokens = tokens->next;
		}
		// printf("argv[0]:%s\n",cmd->argv[0]);
		// printf("argv[1]:%s\n",cmd->argv[1]);
		if (*cmd_list == NULL)
		{
			// printf("42ogitsu\n");
			*cmd_list = ft_dlstnew(cmd);
		}
		else
		{
			// printf("43ogitsu\n");
			ft_dlstadd_back(cmd_list, ft_dlstnew(cmd));
			// printf("end\n");
		}
		if (tokens != NULL)
			tokens = tokens->next;
		// printf("tokens->next\n");
	}
	return (cmd_list);
}


// < file1 cat 
// cat < file1 << EOF > out1 >> out2
// t_cmd {
// 	**argv // cat
// 	*input = t_dlist {
// 		cont = t_redir{
// 			file = "file1"
// 			type = REDIR_INPUT
// 		}
// 		nxt = {
// 			cont = {
// 				file = "EOF"
// 				type = REDIR_HERDOC
// 			}
// 		}
// 	}
// 	*output = {
// 		cont = {
// 			file = "out1"
// 			type = REDIR_OUTPUT
// 		}
// 		nxt = {
// 			cont = {
// 				file = "EOF"
// 				type = REDIR_APPEND
// 			}
// 		}
// 	}
// }


// typedef struct s_dlist
// {
// 	void			*cont;
// 	struct s_dlist	*nxt;
// 	struct s_dlist	*prv;
// }					t_dlist;

// typedef struct s_redir
// {
// 	char			*file;
// 	t_redir_type	type;
// }					t_redir;

// typedef struct s_cmd
// {
// 	char			**argv;
// 	t_dlist			**envp;
// 	char			*path;
// 	t_dlist			*input;
// 	t_dlist			*output;
// 	int				pipe[2];
// 	int				stdio[2];
// }					t_cmd;