/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 16:52:08 by kogitsu           #+#    #+#             */
/*   Updated: 2023/02/13 17:17:42 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*res_lst;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	res_lst = NULL;
	while (lst != NULL)
	{
		new = ft_lstnew(f(lst->content));
		if (new == NULL)
		{
			ft_lstclear(&res_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&res_lst, new);
		lst = lst->next;
	}
	return (res_lst);
}
