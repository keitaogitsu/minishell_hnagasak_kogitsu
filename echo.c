/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:08:27 by hnagasak          #+#    #+#             */
/*   Updated: 2023/12/05 14:40:56 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

# include <stdio.h>

void ft_echo(char *argv[])
{
    printf("--- ft_echo ---\n");
    // オプションの有無を確認
    if(ft_strncmp("-n",argv[1],2) == 0)
        printf("has -n option\n");
    int i = 0;
    while(argv[i] != NULL)
    {
        // printf("argv[%d]:'%s'\n",i,argv[i]);
        printf("%s",argv[i]);
        i++;
    }
    
}

int main(int argc, char *argv[])
{
    printf("--- main ---\n");
    ft_echo(argv);
}