/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:21:27 by kogitsu           #+#    #+#             */
/*   Updated: 2023/12/17 18:05:03 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


char *char_to_string(char c) 
{
    char *str = (char *)malloc(2 * sizeof(char)); // Allocate memory for 2 characters
    if (str == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    str[0] = c;   // Set the first character
    str[1] = '\0'; // Set the null terminator

    return str;
}

t_list *split_delimiters(char *line, char delimiter)
{
    t_list *tokens_list;
    char **tmp;
    int i;
    int tokens_size;
    char *delim_str;
    t_token *new_token;
    t_token *delim_token;
    t_list **save_list;
    t_list *tmp1_list;
    t_list *tmp2_list;
    
    i = 0;
    tmp = ft_split(line, delimiter);
    delim_str = char_to_string(delimiter);
    while (tmp[i] != NULL)
    {
        i++;
    }
    tokens_size = 2 * i - 1;
    tokens_list = NULL;
    while (*tmp != NULL)
    {
      if (ft_lstsize(tokens_list) == 0)
      {
        new_token = (t_token *)malloc(sizeof(t_token));
        new_token->str = *tmp;
        tokens_list = ft_lstnew(new_token);
        delim_token = (t_token *)malloc(sizeof(t_token));
        delim_token->str = ft_strdup(delim_str);
        ft_lstadd_back(&tokens_list, ft_lstnew(delim_token));
      }
      else
      {
        new_token = (t_token *)malloc(sizeof(t_token));
        new_token->str = *tmp;
        ft_lstadd_back(&tokens_list, ft_lstnew(new_token));
        delim_token = (t_token *)malloc(sizeof(t_token));
        delim_token->str = ft_strdup(delim_str);
        ft_lstadd_back(&tokens_list, ft_lstnew(delim_token));
      }
      tmp++;
    }
    tmp1_list = ft_lstlast(tokens_list);
    tmp2_list = tokens_list;
    while (tmp2_list->next->next != NULL)
    {
      tmp2_list = tmp2_list->next;
    }
    tmp2_list->next = NULL;
    free(((t_token *)tmp1_list->content)->str);
    free(tmp1_list->content);
    
    // printf("tmp_list %s\n", ((t_token *)(tmp_list)->content)->str);
    // tokens_list->content = NULL;
    // free(tokens_list);
    
    // while (tokens_list != NULL)
    // {
    //   printf("tokens_list %s\n", ((t_token *)(tokens_list)->content)->str);
    //   tokens_list = tokens_list->next;
    // }
    return (tokens_list);
}

// int split_size(char **str_arr)
// {
// 	int i;
// 	i = 0;
// 	while(str_arr[i] != NULL)
// 		i++;
// 	return i;
// }

// int sum_sizes(int *sizes)
// {
// 	int i;
// 	i = 0;
// 	while(&(sizes[i]) != NULL)
// 		i++;
// 	return i;
// }

t_list *tokenize(char *line)
{
    t_list *tokens_list;
    int i;
    int list_size;
    t_list *tmp_list;
    t_list *tmp;
    t_list *tmp_of_tmp_list;

    i = 0;
    tokens_list = split_delimiters(line, '|');
		// list_size = ft_lstsize(tokens_list);
    tmp_list = NULL;
    while (tokens_list->next != NULL)
    {
      tmp_list = split_delimiters(((t_token *)(tokens_list)->content)->str, '<');
      while (tmp_list->next != NULL)
      {
        printf("1.tmp_list %s\n", ((t_token *)(tmp_list)->content)->str);
        tmp_list = tmp_list->next;
      }
      ft_lstlast(tmp_list)->next = tokens_list->next;
      tokens_list = tokens_list->next;
      i++;
    }
    tokens_list = tmp;
    tmp_list = NULL;
    while (tokens_list->next != NULL)
    {
      if (tmp_list == NULL)
      {
        tmp_list = split_delimiters(((t_token *)(tokens_list)->content)->str, '>');
        tmp = tmp_list;
      }
      else
        tmp_list = split_delimiters(((t_token *)(tokens_list)->content)->str, '>');
      while (tmp_list->next != NULL)
      {
        printf("2.tmp_list %s\n", ((t_token *)(tmp_list)->content)->str);
        tmp_list = tmp_list->next;
      }
      ft_lstlast(tmp_list)->next = tokens_list->next;
      tokens_list = tokens_list->next;
    }
    tokens_list = tmp;
    while (tokens_list != NULL)
    {
      printf("tokens_list %s\n", ((t_token *)(tokens_list)->content)->str);
      tokens_list = tokens_list->next;
    }
		// 再分割したあとの全体のtoken_sizeと再分割した配列(tmp)を取得
		// tmp = (char ***) malloc(sizeof(char **) * (tokens_size + 1));
		// sizes = (int *) malloc(sizeof(int) * (tokens_size + 1));
    // while (tokens_list[i] != NULL){
		// 	tmp[i] = split_delimiters(tokens_list[i],'>');
		// 	sizes[i] = split_size(tmp);
    //   i++;
		// }
		// tmp[i] = NULL;
		// sizes[i] = NULL;

		// TODO:元のtokensを全部freeする
		// tokens_size = sum_sizes(sizes);
		// tokens_list = (char **) malloc(sizeof(char *) * (tokens_size + 1));
		// while(i < tokens_size)
		// {
		// 	int j = 0;
    //   while(tmp[i][j] != NULL)
		// 	{
		// 		tokens_list[i] = tmp[j];
		// 		i++;
		// 		j++;
		// 	}
		// }
    // for (int i = 0; tokens_list[i] != NULL ; i++)
		// 	printf("tokens_list[%d] %s\n", i, tokens_list[i]);
    return (tokens_list);
}