/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:40:45 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/17 14:07:22 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_dlist	*ft_dlstnew(void *content)
{
	t_dlist	*list;

	list = (t_dlist *)malloc(sizeof(t_dlist));
	if (list == NULL)
		malloc_error_exit();
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
		new->i = 0;
		return ;
	}
	last = *lst;
	while (last->nxt != NULL)
		last = last->nxt;
	last->nxt = new;
	new->prv = last;
	new->i = last->i + 1;
}

/**
 * @brief Set the index for each element in a doubly linked list.
 * This function iterates through a doubly linked list and assigns an
 * index to each element. The index starts at 0 and increments by 1
 * for each successive element in the list.
 *
 * @param lst A pointer of the first element of the doubly linked list.
 * The list is assumed to be non-NULL and properly initialized.
 * Elements of the list should have a member 'i' to store the index,
 * and a member 'nxt' which is a pointer to the next element in the list.
 *
 * @note The function does not return a value.
 * It directly modifies the 'i' member
 * of each element in the list to set the index.
 * It is the caller's responsibility to ensure that the list is non-empty
 * and each element of the list is properly allocated.
 */
void	set_lstidx(t_dlist **lst)
{
	t_dlist	*current;
	size_t	i;

	current = *lst;
	i = 0;
	while (current != NULL)
	{
		current->i = i;
		current = current->nxt;
		i++;
	}
}

size_t	ft_dlstsize(t_dlist **lst)
{
	size_t	i;
	t_dlist	*current;

	current = *lst;
	i = 0;
	while (current != NULL)
	{
		current = current->nxt;
		i++;
	}
	return (i);
}

void	ft_errmsg(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
}
