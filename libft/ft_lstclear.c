/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:32:48 by kogitsu           #+#    #+#             */
/*   Updated: 2023/12/09 21:26:35 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cp_lst;

	if (lst == NULL || del == NULL || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		cp_lst = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = cp_lst;
	}
}
