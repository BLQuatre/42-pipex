/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:28:14 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/29 05:02:55 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
0 pipex		argc - 5
1 infile	argc - 4
2 cmd1		argc - 3
3 cmd2		argc - 2
4 outfile	argc - 1
argc == 5
Last arg > argc - 1 == outfile
*/

void	get_cmds(t_pipex *pipex, int argc, char **argv)
{
	t_list	*cmds;
	t_list	*tmp_cmd;
	t_cmd	*cmd;
	int		i;

	i = 2;
	cmds = NULL;
	while (argv[i] && i < argc - 1)
	{
		cmd = ft_cmd_get(argv[i]);
		if (!cmd)
			quit(1, MALLOC_FAILED_MSG, pipex);
		tmp_cmd = ft_lstnew(cmd);
		if (!tmp_cmd)
			quit(1, MALLOC_FAILED_MSG, pipex);
		ft_lstadd_back(&cmds, tmp_cmd);
		i++;
	}
	pipex->cmds = cmds;
}

void	check_args(t_pipex *pipex, char *infile, char *outfile)
{
	int fd;

	if (access(infile, R_OK) == -1)
		quit(1, NOT_ENOUGH_PERMS, pipex);
	fd = open(infile, O_RDONLY);
	if (fd < 0)
		quit(1, "no infile", pipex);
	close(fd);
	fd = open(outfile, O_WRONLY | O_RDONLY | O_CREAT, 0644);
	if (fd < 0)
		quit(1, "no outfiele", pipex);
	close(fd);
}

void	read_from_file(t_pipex *pipex, char *filename)
{
	if (pipex->here_doc)
	{
		return ;
	} // TODO: manage here doc
	
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		quit(1, "eeee", pipex);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

// void exec_cmd(t_list *cmd, t_pipex *pipex, char **envp)
// {
// 	print_cmd((t_cmd *) cmd->content);
// 	// cmd = cmd->next;
// 	int pd[2];
// 	if (pipe(pd) == -1)
// 		quit(1, "PIPE NOT DONE", pipex);
// 	pid_t pid = fork();
// 	if (pid < 0)
// 		quit(1, "pid not done", pipex);
	
// 	if (pid == 0) {
// 		dup2(pipex->in_fd, STDIN_FILENO);
// 		close(pipex->in_fd);
// 		dup2(pd[1], STDIN_FILENO);
// 		close(pd[0]);
// 		close(pd[1]);
// 		printf("[DEBUG] Child: Executing `%s`...\n",
// 			((t_cmd *) cmd->content)->cmd
// 		);
// 		execve(
// 			((t_cmd *) cmd->content)->cmd,
// 			((t_cmd *) cmd->content)->args,
// 			envp
// 		);
// 	}
	
// 	dup2(pd[0], STDOUT_FILENO);
// 		close(pd[0]);
// 		close(pd[1]);
// 		printf("[DEBUG] Child: Executing `%s`...\n",
// 			((t_cmd *) cmd->content)->cmd
// 		);
// 		execve(
// 			((t_cmd *) cmd->content)->cmd,
// 			((t_cmd *) cmd->content)->args,
// 			envp
// 		);
// 	waitpid(pid, NULL, 1);
// 	printf("[DEBUG] Pid `%d` ended\n", pid);
// }

int	main(int argc, char **argv, char **envp)
{
	t_pipex *pipex;
	t_list	*tmp_cmd;

	if (argc < 5)
		quit(1, WRONG_ARGS_NB_MSG, NULL);
	pipex = ft_calloc(1, sizeof(t_pipex));
	check_args(pipex, argv[1], argv[argc - 1]);
	get_cmds(pipex, argc, argv);

	read_from_file(pipex, argv[1]);
	




	tmp_cmd = pipex->cmds;
	// while (tmp_cmd)
	// {
	// 	exec_cmd(tmp_cmd, pipex, envp);
	// 	tmp_cmd = tmp_cmd->next;
	// }

	// printf("Starting duping the pipe\n");
	// int fd_in = open(infile, O_WRONLY | O_APPEND);
	// int fd_out = open(outfile, O_WRONLY | O_APPEND);
	// printf("Duping pipe %d to pipe %d\n", fd_in, STDIN_FILENO);
	// dup2(fd_in, STDIN_FILENO);
	// printf("Duping pipe %d to pipe %d\n", fd_out, STDOUT_FILENO);
	// dup2(fd_out, STDOUT_FILENO);
	// printf("Pipes: %d & %d\n", fd_in, fd_out);
	// close(fd_in);
	// close(fd_out);

	// int pd[2]; //Pipe descriptor
	// pipe(pd);

	// int pid = fork();
	// if (pid < 0) perror("Something failed on trying to create a child process!\n");
	// else if (pid == 0) { //Child
	// 	dup2(pd[1], STDIN_FILENO);
	// 	close(pd[0]);
	// 	close(pd[1]);
	// 	printf("[DEBUG] Child: Executing `%s`...\n",
	// 		((t_cmd *) cmds->content)->cmd
	// 	);
	// 	execve(
	// 		((t_cmd *) cmds->content)->cmd,
	// 		((t_cmd *) cmds->content)->params,
	// 		NULL
	// 	);
	// } else { //Parent
	// 	dup2(pd[0], STDOUT_FILENO);
	// 	close(pd[0]);
	// 	close(pd[1]);
	// 	printf("[DEBUG] Child: Executing `%s`...\n",
	// 		((t_cmd *) cmds->content)->cmd
	// 	);
	// 	execve(
	// 		((t_cmd *) cmds->content)->cmd,
	// 		((t_cmd *) cmds->content)->params,
	// 		NULL
	// 	);
	// }
	// // if (pid == 0)
	// // {
	// // 	printf("[DEBUG] Child: Executing `%s`...\n",
	// // 		((t_cmd *) cmds->content)->cmd
	// // 	);
	// // 	execve(
	// // 		((t_cmd *) cmds->content)->cmd,
	// // 		((t_cmd *) cmds->content)->params,
	// // 		NULL
	// // 	);
	// // }
	// waitpid(pid, NULL, 1);
	// printf("[DEBUG] Pid `%d` ended\n", pid);

	// ft_lstclear(&cmds, (void (*)(void *))ft_cmd_free);
}

// //main()
// {
// 	ft_init_pipex() why
// 	ft_check_args() done
// 	ft_parse_cmds() done
// 	ft_parse_args() done
// 	while (cmds) wip
// 		ft_exec()
// 	ft_cleanup() no
// }