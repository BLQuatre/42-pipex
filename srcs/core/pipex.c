/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:28:14 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/27 02:01:56 by cauvray          ###   ########.fr       */
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

t_list	*get_cmds(int argc, char **argv)
{
	t_list	*cmds;
	t_list	*tmp;
	t_cmd	*cmd;
	int		i;

	i = 1;
	cmds = NULL;
	while (argv[i] && i < argc - 1)
	{
		cmd = ft_cmd_get(argv[i]);
		if (!cmd)
			quit(1, "Errro2");
		tmp = ft_lstnew(cmd);
		if (!tmp)
			quit(1, "Erro3");
		ft_lstadd_back(&cmds, tmp);
		i++;
	}
	return (cmds);
}

int	main(int argc, char **argv)
{
	t_list	*cmds;
	t_list	*tmp;
	char	*outfile;
	char	*infile;

	if (argc < 5)
		quit(1, "Erro1");
	printf("Outfile: `%s`\n", outfile = argv[1]);
	printf("Infile: `%s`\n", infile = argv[argc - 1]);
	cmds = get_cmds(argc, argv);
	tmp = cmds;
	while (tmp)
	{
		print_cmd((t_cmd *) tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&cmds, (void (*)(void *))ft_cmd_free);
}
