/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:56:06 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/27 22:49:20 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	quit(int exit_code, char *msg, t_pipex *pipex)
{
	if (pipex)
		free(pipex);
	if (exit_code >= 1)
	{
		write(2, "Error\n", 6);
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
	exit(exit_code);
}
