/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 01:44:08 by cauvray           #+#    #+#             */
/*   Updated: 2024/12/06 20:35:22 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file_name, int flags, int exit_on_error)
{
	int	fd;

	fd = open(file_name, flags, 0777);
	if (fd <= -1)
	{
		show_error(file_name, 0);
		if (exit_on_error)
			exit(1);
	}
	return (fd);
}

// int	check_files(char *file_in, char *file_out)
// {
// 	fd_out = open_file(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
// }