/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:40:45 by hnagasak          #+#    #+#             */
/*   Updated: 2024/01/04 17:32:22 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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