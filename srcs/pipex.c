/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 05:56:08 by cauvray           #+#    #+#             */
/*   Updated: 2024/12/05 01:16:18 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exec(char *str_cmd, char **envp)
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
	perror("pb");
}

void	pipe_cmd(char *str_cmd, char **envp)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		perror("zoulou");
	pid = fork();
	if (pid < 0)
		perror("zoulou2");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec(str_cmd, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		// waitpid(pid, NULL, 0);
	}
}

int open_file(char *file_name, int flags)
{
	int	fd;

	fd = open(file_name, flags, 0777);
	if (fd <= -1)
	{
		show_error(file_name, 0);
		exit(1);
	}
	return (fd);
}


int	main(int argc, char *argv[], char *envp[])
{
	int		fd_in;
	int		fd_out;
	int		i;

	i = 1;
	if (ft_strncmp(argv[i++], "here_doc", 9) == 0)
	{
		fd_out = open_file(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
		init_heredoc(argv[i++]);
	} else {
		fd_in = open_file(argv[1], O_RDONLY);
		fd_out = open_file(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	while (i < argc - 2)
		pipe_cmd(argv[i++], envp);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	exec(argv[i], envp);
	return (0);
}
