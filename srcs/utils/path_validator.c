/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 01:45:42 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/28 09:17:52 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "utils.h"
#include <sys/stat.h>

int	is_executable_file(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (0);
	if (S_ISREG(buf.st_mode) && (buf.st_mode & S_IXUSR))
		return (1);
	return (0);
}

int	is_updatable_file(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (0);
	if (S_ISREG(buf.st_mode) && (buf.st_mode & S_IWUSR))
		return (1);
	return (0);
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}
