/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:24:54 by cauvray           #+#    #+#             */
/*   Updated: 2024/12/05 03:55:21 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_heredoc_input(char *limiter, int *fds)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 0);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			get_next_line(-1);
			free(line);
			close(fds[1]);
			exit(0);
		}
		ft_putstr_fd(line, fds[1]);
		free(line);
	}
	get_next_line(-1);
	close(fds[1]);
}

void	init_heredoc(char *limiter)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return (perror("pipe error"), exit(1));
	pid = fork();
	if (pid < 0)
		return (perror("fork error"), close(fd[0]), close(fd[1]), exit(1));
	if (pid == 0)
	{
		close(fd[0]);
		get_heredoc_input(limiter, fd);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}
