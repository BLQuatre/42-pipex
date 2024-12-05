/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 02:19:35 by cauvray           #+#    #+#             */
/*   Updated: 2024/12/05 02:56:48 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	dup2_close(int dup_from, int dup_to)
{
	dup2(dup_from, dup_to);
	close(dup_from);
}

void	exec(char *str_cmd, char **envp)
{
	char	**args;
	char	*cmd;

	if (!str_cmd)
		return ;
	args = ft_split(str_cmd, ' ');
	if (!args)
		return ;
	if (!args[0])
	{
		free_tab(args);
		return (ft_putstr_fd(str_cmd, 2),
			ft_putstr_fd(": command not found\n", 2));
	}
	cmd = env_get_cmd_path(envp, args[0]);
	if (!cmd)
	{
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (free_tab(args));
	}
	execve(cmd, args, envp);
	free(cmd);
	free_tab(args);
	perror("failed to execute command");
}

int	pipe_cmd(char *str_cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror("pipe error"), exit(1), 0);
	pid = fork();
	if (pid < 0)
		return (perror("fork error"), close(fd[0]), close(fd[1]), exit(1), 0);
	if (pid == 0)
	{
		close(fd[0]);
		dup2_close(fd[1], STDOUT_FILENO);
		exec(str_cmd, envp);
		return (0);
	}
	else
	{
		close(fd[1]);
		dup2_close(fd[0], STDIN_FILENO);
		return (pid);
	}
}
