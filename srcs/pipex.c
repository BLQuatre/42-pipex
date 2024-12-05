/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 05:56:08 by cauvray           #+#    #+#             */
/*   Updated: 2024/12/05 04:03:37 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_pipex(int argc, char *argv[], int *fd_in, int *i)
{
	int	tmp_fd_out;

	*i = 2;
	tmp_fd_out = open_file(argv[argc - 1], O_CREAT);
	close(tmp_fd_out);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc >= 6)
	{
		init_heredoc(argv[2]);
		*i = 3;
	}
	else
	{
		*fd_in = open_file(argv[1], O_RDONLY);
		dup2_close(*fd_in, STDIN_FILENO);
	}
}

void	pid_add_to_lst(t_list **lst, int pid)
{
	t_list	*new;

	if (pid == 0)
		return ;
	new = ft_lstnew(&pid);
	if (!new)
		return ;
	ft_lstadd_back(lst, new);
}

void	wait_pids(t_list *pids, int *exit)
{
	while (pids)
	{
		waitpid(*((int *) pids->content), exit, 0);
		pids = pids->next;
	}
}

void	do_nothing(void *content)
{
	(void) content;
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd_in;
	int		fd_out;
	int		i;
	t_list	*pids;
	int		exit;

	exit = 0;
	if (argc <= 4)
		return (ft_putstr_fd(WRONG_ARGS_MSG, 2), 1);
	init_pipex(argc, argv, &fd_in, &i);
	pids = NULL;
	while (i < argc - 2)
		pid_add_to_lst(&pids, pipe_cmd(argv[i++], envp));
	wait_pids(pids, &exit);
	ft_lstclear(&pids, do_nothing);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc >= 6)
		fd_out = open_file(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
	else
		fd_out = open_file(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
	dup2_close(fd_out, STDOUT_FILENO);
	exec(argv[i], envp);
	return (exit);
}
