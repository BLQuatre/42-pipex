/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:18:36 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/27 23:30:32 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	*ft_cmd_get(char *str)
{
	t_cmd	*cmd;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (str[i] && str[i] != ' ')
		i++;
	if (i < ft_strlen(str) && str[i + 1])
		cmd->args = ft_split(str, ' ');
	cmd->cmd = ft_substr(str, 0, i);
	if (!cmd->cmd)
		return (NULL);
	return (cmd);
}

void	ft_cmd_free(t_cmd *cmd)
{
	int	params_len;

	free(cmd->cmd);
	params_len = ft_tab_len(cmd->args);
	while (params_len--)
		free(cmd->args[params_len]);
	free(cmd->args);
	free(cmd);
}
