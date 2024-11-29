/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 05:56:08 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/29 08:15:44 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[], char *envp[])
{
	if (argc < 5)
	{
		error("pipex", WRONG_ARGS_MSG, "./pipex infile cmd1 cmd2 outfile", 1);
		return (1);
	}
	int fd[2];
	if (pipe(fd) == -1)
		return (1);
	int pid1 = fork();
	if (pid1 < 0)
		return (1);
	if (pid1 == 0)
	{
		char **cmd = ft_split(argv[2], ' ');
		int file_fd = open(argv[1], O_RDONLY);
		if (file_fd < 0)
			error(ft_getenv(envp, "SHELL"), PERMISSION_DENIED, argv[1], 1);
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);

		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(ft_getpath(envp, cmd[0]), cmd, envp);
		error(ft_getenv(envp, "SHELL"), CMD_NOT_FOUND_MSG, cmd[0], 127);
	}
	close(fd[1]);
	int pid2 = fork();
	if (pid2 < 0)
		return 3;
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		char **cmd = ft_split(argv[3], ' ');
		int file_fd2 = open(argv[4], O_RDONLY | O_WRONLY | O_CREAT, 0644);
		if (file_fd2 < 0)
			error(ft_getenv(envp, "SHELL"), PERMISSION_DENIED, argv[4], 1);
		dup2(file_fd2, STDOUT_FILENO);
		close(file_fd2);
		execve(ft_getpath(envp, cmd[0]), cmd, envp);
		error(ft_getenv(envp, "SHELL"), CMD_NOT_FOUND_MSG, cmd[0], 127);
	}
	close(fd[0]);
	int exit_status = 0;
	waitpid(pid1, &exit_status, 0);
	waitpid(pid2, &exit_status, 0);
	if (exit_status > 0)
		return (127);
	return (0);
}
