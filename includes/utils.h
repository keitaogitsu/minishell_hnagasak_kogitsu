/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:45:23 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/25 20:09:31 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"
# include <stdarg.h>
# include <stdio.h>

# define IS_SHELL_VAR 1

typedef struct s_dlist
{
	void			*cont;
	size_t			i;
	struct s_dlist	*nxt;
	struct s_dlist	*prv;
}					t_dlist;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_shell_var;
}					t_env;

// envp.c
void				get_key_value(char *envp, char **key, char **value);
size_t				get_argc(char *argv[]);
int					is_env_key_char(char c);
char				**envlist2arr(t_dlist **env_list);

int					is_executable_file(char *path);
int					is_directory(const char *path);
int					is_updatable_file(char *path);

// list.c
t_dlist				*ft_dlstnew(void *content);
void				ft_dlstadd_back(t_dlist **lst, t_dlist *new);
size_t				ft_dlstsize(t_dlist **lst);
void				ft_errmsg(char *msg);

// t_env.c
t_env				*find_existing_env(char *str_env, t_dlist **env_list);
t_env				*to_env(char *envp, int is_shell_var);
t_dlist				**init_env(char **envp);
void				update_env_value(t_dlist **env_list, char *envp);
void				remove_env(char *key, t_dlist **env_list);

// malloc.c
char				*ft_malloc(size_t size);
void				malloc_error_exit(void);

#endif