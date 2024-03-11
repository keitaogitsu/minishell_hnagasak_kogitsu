/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:13:48 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/07 02:25:13 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// ファイルディスクリプタを閉じる。成功したら初期値(-1)を返す。
// 失敗したら引数のfdをそのまま返す
int	ft_close(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
		{
			perror("ft_close error::");
			return (fd);
		}
		else
		{
			ft_debug("    close fd:%d\n", fd);
			return (-1);
		}
	}
	return (fd);
}

void	ft_pipe(int fd[2])
{
	if (pipe(fd) == -1)
		perror("pipe error");
	else
		ft_debug("[set_pipe] fd(%d,%d)\n", fd[0], fd[1]);
}

int	delete_file(const char *filepath)
{
	ft_debug("--- delete_file [%s]---\n", filepath);
	if (unlink(filepath) == 0)
	{
		ft_debug("'%s' が正常に削除されました。\n", filepath);
		return (0);
	}
	else
	{
		perror("ファイルの削除に失敗しました");
		return (-1);
	}
}

int	file_open(char *file, int flag, int mode)
{
	int	fd;

	fd = open(file, flag, mode);
	if (fd == -1)
	{
		ft_errmsg("minishell: ");
		ft_errmsg(file);
		ft_errmsg(": ");
		ft_errmsg(strerror(errno));
		exit(EXIT_FAILURE);
	}
	return (fd);
}

/**
 * @brief free a NULL-terminated char double pointer.
 * @param arr NULL-terminated char double pointer
 * @note double pointer must be NULL-terminated.
 */
void	free_strarr(char **arr)
{
	int	i;

	if (arr == NULL)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
