/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:44:19 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/27 23:47:39 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
	{
		printf("NO CMD\n");
		return ;
	}
	printf("-----CMD-----\n");
	printf("Cmd   : `%s`\n", cmd->cmd);
	printf("Args  : `%d` (%p)\n", ft_tab_len(cmd->args), cmd->args);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			printf("  [%d] = `%s`\n", i, cmd->args[i]);
			i++;
		}
	}
}

void	print_params(int argc, char **argv)
{
	int		i;
	int		j;
	char	**args;

	printf("Args: `%d`\n", argc);
	i = 1;
	while (argv[i])
	{
		printf("  argv[%d] = `%s`\n", i, argv[i]);
		args = ft_split(argv[i], ' ');
		if (ft_tab_len(args) > 1)
		{
			j = 0;
			while (args[j])
			{
				printf("    args[%d] = `%s`\n", j, args[j]);
				j++;
			}
		}
		i++;
	}
}
