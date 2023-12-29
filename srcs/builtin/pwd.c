/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 09:41:01 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/29 09:41:11 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_pwd(void)
{
	char	*path;

	// printf("--- ft_pwd ---\n");
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}
