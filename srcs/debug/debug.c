/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:44:19 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/27 00:23:31 by cauvray          ###   ########.fr       */
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
	printf("Args  : `%d` (%p)\n", ft_tab_len(cmd->params), cmd->params);
	if (cmd->params)
	{
		i = 0;
		while (cmd->params[i])
		{
			printf("  [%d] = `%s`\n", i, cmd->params[i]);
			i++;
		}
	}
}

void	print_params(int argc, char **argv)
{
	int		i;
	int		j;
	char	**params;

	printf("Args: `%d`\n", argc);
	i = 1;
	while (argv[i])
	{
		printf("  argv[%d] = `%s`\n", i, argv[i]);
		params = ft_split(argv[i], ' ');
		if (ft_tab_len(params) > 1)
		{
			j = 0;
			while (params[j])
			{
				printf("    params[%d] = `%s`\n", j, params[j]);
				j++;
			}
		}
		i++;
	}
}
