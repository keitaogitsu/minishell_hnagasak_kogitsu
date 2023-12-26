/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:40:45 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/27 03:05:39 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*list;

	list = (t_dlist *)malloc(sizeof(t_dlist));
	if (list == NULL)
		return (NULL);
	list->cont = content;
	list->nxt = NULL;
	list->prv = NULL;
	return (list);
}

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
last = *lst;
	while (last->nxt != NULL)
		last = last->nxt;
	last->nxt = new;
	new->prv = last;
}

void print_env(t_dlist *env_list)
{
	t_env	*env;
	t_dlist	*current;

	current = env_list;
	printf("--- print_env ----\n");
	while (current)
	{
		// printf("## current:%p, %p\n", current, current->cont);
		env = current->cont;
		printf("%s=%s , is_shell_var = %d\n", env->key,env->value, env->is_shell_var);
		// printf("is_shell_var: %d\n", env->is_shell_var);
		current = current->nxt;
	}
	printf("--- end print_env ----\n");
}