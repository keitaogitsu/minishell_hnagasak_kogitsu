/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:57:38 by hnagasak          #+#    #+#             */
/*   Updated: 2024/05/30 22:00:15 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	free_tmp(t_token *tmp, t_token *expanded_tokens)
{
	if (expanded_tokens == NULL)
	{
		free(tmp->str);
		free(tmp);
	}
}
