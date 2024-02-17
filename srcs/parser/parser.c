/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 14:20:30 by kogitsu           #+#    #+#             */
/*   Updated: 2024/02/17 15:11:01 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	process_redir(t_token **tokens, t_cmd *cmd, t_redir *redir, 
						t_redir_type redir_type)
{
	
	*tokens = (*tokens)->next;
	redir = crt_redir((*tokens)->str, redir_type);
	cmd_output_join(cmd, redir);
}

void	create_cmd(t_token **tokens, t_cmd *cmd, t_redir *redir, size_t *i)
{
	t_token *token;
	
	token = *tokens;
	if (token->type == CHAR_GENERAL || token->type == CHAR_QUOTE 
	|| token->type == CHAR_DQUOTE)
	{
		cmd->argv[*i] = token->str;
		*i = *i + 1;
	}
	else if (token->type == CHAR_GREATER)
		process_redir(tokens, cmd, redir, REDIR_OUTPUT);
	else if (token->type == CHAR_LESSER)
		process_redir(tokens, cmd, redir, REDIR_INPUT);
	else if (token->type == D_GREATER)
		process_redir(tokens, cmd, redir, REDIR_APPEND);
	else if (token->type == D_LESSER)
		process_redir(tokens, cmd, redir, REDIR_HEREDOC);
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
		i = 0;
		cmd = cmd_init(tokens, env_list);
		while (tokens != NULL && tokens->type != CHAR_PIPE)
		{
			create_cmd(&tokens, cmd, redir, &i);
			tokens = tokens->next;
		}
		if (*cmd_list == NULL)
			*cmd_list = ft_dlstnew(cmd);
		else
			ft_dlstadd_back(cmd_list, ft_dlstnew(cmd));
		if (tokens != NULL)
			tokens = tokens->next;
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