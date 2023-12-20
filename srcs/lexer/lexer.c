/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kogitsu <kogitsu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:21:27 by kogitsu           #+#    #+#             */
/*   Updated: 2023/12/20 23:30:30 by kogitsu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*char_to_string(char c)
{
	char *str = (char *)malloc(2 * sizeof(char));
		// Allocate memory for 2 characters
	if (str == NULL)
	{
		// Handle memory allocation failure
		return (NULL);
	}
	str[0] = c;    // Set the first character
	str[1] = '\0'; // Set the null terminator
	return (str);
}

t_list	*split_delimiters1(char *line, char delimiter)
{
	t_list	*tokens_list;
	char	**tmp;
	int		i;
	int		tokens_size;
	char	*delim_str;
	t_token	*new_token;
	t_token	*delim_token;
	t_list	**save_list;
	t_list	*tmp1_list;
	t_list	*tmp2_list;

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

// cat <> >< <<
char	**ft_split_redir2(char *line, char *delimiter)
{
	int		i;
	int		j;
	int		k;
	int		wc;
	char	**out;

	i = 0;
	j = 0;
	k = 0;
	wc = 0;
	while (line[i])
	{
		while (line[i] && ((line[i] == '<' && line[i + 1] == '<')
				|| (line[i] == '>' && line[i + 1] == '>')))
			i = i + 2;
		if (line[i])
			wc++;
		while (line[i] && (line[i] != '<' && line[i] != '>'))
			i++;
	}
	out = (char **)malloc(sizeof(char *) * (wc + 1));
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'
				|| line[i] == '\n'))
			i++;
		j = i;
		while (line[i] && (line[i] != ' ' && line[i] != '\t'
				&& line[i] != '\n'))
			i++;
		if (i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			ft_strlcpy(out[k++], &line[j], i - j);
		}
	}
	out[k] = NULL;
	return (out);
}

t_list	*split_delimiters2(char *line, char *delimiter)
{
	t_list	*tokens_list;
	char	**tmp;
	int		i;
	int		tokens_size;
	char	*delim_str;
	t_token	*new_token;
	t_token	*delim_token;
	t_list	**save_list;
	t_list	*tmp1_list;
	t_list	*tmp2_list;

	i = 0;
	tmp = ft_split_redir2(line, delimiter);
	// delim_str = char_to_string(delimiter);
	delim_str = delimiter;
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

void	print_tokens_list(t_list *tokens_list, int n)
{
	while (tokens_list != NULL)
	{
		printf("%d.tokens_list %s\n", n,
			((t_token *)(tokens_list)->content)->str);
		tokens_list = tokens_list->next;
	}
}

t_list	*tokenize(char *line)
{
	t_list *tokens_list;
	int i;
	int list_size;
	t_list *tmp_list;
	t_list *tmp;
	t_list *current;
	t_list *tmp_of_tmp_list;
	t_list *splited_pipe;
	t_list *splited_lessthan;
	t_list *first_token;

	splited_pipe = split_delimiters1(line, '|');
	first_token = NULL;
	current = splited_pipe;
	while (current != NULL)
	{
		if (first_token == NULL)
			first_token = split_delimiters1(((t_token *)(current)->content)->str,
					'<');
		else
			ft_lstlast(first_token)->next = split_delimiters1(((t_token *)(current)->content)->str,
					'<');
		current = current->next;
	}
	print_tokens_list(first_token, 10);
	current = first_token;
	first_token = NULL;
	while (current != NULL)
	{
		if (first_token == NULL)
			first_token = split_delimiters1(((t_token *)(current)->content)->str,
					'>');
		else
			ft_lstlast(first_token)->next = split_delimiters1(((t_token *)(current)->content)->str,
					'>');
		current = current->next;
	}
	print_tokens_list(first_token, 20);
	current = first_token;
	first_token = NULL;
	while (current != NULL)
	{
		if (first_token == NULL)
			first_token = split_delimiters1(((t_token *)(current)->content)->str,
					' ');
		else
			ft_lstlast(first_token)->next = split_delimiters1(((t_token *)(current)->content)->str,
					' ');
		current = current->next;
	}
	print_tokens_list(first_token, 30);
	tokens_list = tmp;
	// 再分割したあとの全体のtoken_sizeと再分割した配列(tmp)を取得
	// tmp = (char ***) malloc(sizeof(char **) * (tokens_size + 1));
	// sizes = (int *) malloc(sizeof(int) * (tokens_size + 1));
	// while (tokens_list[i] != NULL){
	// 	tmp[i] = split_delimiters1(tokens_list[i],'>');
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