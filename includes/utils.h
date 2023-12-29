/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:45:23 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/29 10:15:20 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <stdio.h>


#define IS_SHELL_VAR 1

typedef struct s_dlist
{
	void			*cont;
	struct s_dlist	*nxt;
	struct s_dlist	*prv;
}					t_dlist;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_shell_var;
}					t_env;

t_dlist				*ft_dlstnew(void *content);
void				ft_dlstadd_back(t_dlist **lst, t_dlist *new);

// t_env.c
t_dlist	**init_env(char **envp);
t_env	*to_env(char *envp, int is_shell_var);

// debug
void				print_env(t_dlist *env_list);

#endif