/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnagasak <hnagasak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:47:06 by hnagasak          #+#    #+#             */
/*   Updated: 2024/03/22 10:52:36 by hnagasak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_STATUS_H
# define EXIT_STATUS_H

# define STATUS_CMD_NOT_FOUND 127  // command not found
# define STATUS_ENOENT 127         // No such file or directory
# define STATUS_EACCES 126         // permission denied
# define STATUS_EISDIR 126         // is a directory
# define STATUS_EINVAL 2           // invalid argument
# define STATUS_NO_NUMERIC_ARG 255 // numeric argument required

#endif