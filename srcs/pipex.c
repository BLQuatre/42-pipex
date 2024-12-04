/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 05:56:08 by cauvray           #+#    #+#             */
/*   Updated: 2024/12/04 15:56:38 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_cmd(t_cmd *cmd, char **envp)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		perror("zoulou");
	pid = fork();
	if (pid < 0)
		perror("zoulou2");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execve(cmd->cmd, cmd->args, envp);
		return ;
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
}

void	init_here_doc(void)
{
	printf("Heredoc pas encore implemete");
}

t_cmd	*get_cmd(char *str_cmd, char **envp)
{
	t_cmd	*cmd;
	char	**args;

	if (!str_cmd)
		return (NULL);
	args = ft_split(str_cmd, ' ');
	if (!args)
		return (NULL);
	if (!args[0])
		return (free(args), NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (ft_free_tab(args), NULL);
	cmd->cmd = ft_getpath(envp, args[0]);
	if (!cmd->cmd)
		return (ft_free_tab(args), NULL);
	cmd->args = args;
	return (cmd);
}

void	get_cmds(t_pipex *pipex, int index, int argc, char **args)
{
	t_cmd	*cmd;
	t_list	*new_cmd;

	while (index < argc - 1)
	{
		cmd = get_cmd(args[index], pipex->envp);
		if (!cmd)
			error(pipex->shell, "aaaa", "zoulou", 1);
		new_cmd = ft_lstnew(cmd);
		if (!new_cmd)
			error(pipex->shell, "eawe aw", "eawwewwwwww", 1);
		ft_lstadd_back(&pipex->cmds, new_cmd);
		index++;
	}
}

t_pipex	*get_pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		i;

	if (argc <= 4)
		error("pipex", WRONG_ARGS_MSG, "./pipex infile cmd cmd outfile", 1);
	pipex = ft_calloc(1, sizeof(t_pipex));
	pipex->envp = envp;
	i = 1;
	if (!ft_strncmp(argv[i++], "here_doc", 9))
	{
		pipex->here_doc = 1;
		pipex->limiter = argv[i++];
	}
	if (pipex->here_doc && argc <= 5)
		error("pipex", WRONG_ARGS_MSG,
			"./pipex here_doc LIMITER cmd cmd outfile", 1);
	pipex->shell = ft_getenv(envp, "SHELL");
	if (!pipex->shell)
		pipex->shell = ft_strdup("bash");
	get_cmds(pipex, i, argc, argv);
	// printf("Pipex info:\n");
	// printf("- shell: %s\n", pipex->shell);
	// t_list	*lst = pipex->cmds;
	// printf("- cmds:\n");
	// while (lst)
	// {
		// printf("  - cmd_path: %s\n", ((t_cmd *) lst->content)->cmd);
		// lst = lst->next;
	// }
	// printf("- here_doc: %s\n", pipex->here_doc ? "Yes" : "No");
	// printf("- here_doc limiter: %s\n", pipex->limiter);
	return (pipex);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int fd_in;
	int fd_out;
	t_list *tmp_cmd;

	pipex = get_pipex(argc, argv, envp);
	if (!pipex)
		return (1);

	if (pipex->here_doc)
	{
		init_here_doc();

	} else {
		fd_in = open(argv[1], O_RDONLY, 0777);
		fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		dup2(fd_in, STDIN_FILENO);
	}
	tmp_cmd = pipex->cmds;
	while (tmp_cmd->next)
	{
		pipe_cmd((t_cmd *) tmp_cmd->content, envp);
		tmp_cmd = tmp_cmd->next;
	}
	dup2(fd_out, STDOUT_FILENO);
	execve(((t_cmd *) tmp_cmd->content)->cmd, ((t_cmd *) tmp_cmd->content)->args, envp);
	return (0);
}
