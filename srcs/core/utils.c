/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 05:49:15 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/29 06:47:37 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*ft_getenv(char **envp, char *env_name)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		if (!ft_strchr(envp[i], '='))
			continue ;
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		if (!ft_strncmp(envp[i], env_name, j))
			return (ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (NULL);
}

char	*ft_getpath(char **envp, char *cmd)
{
	char	**paths;
	int		i;
	char	*path;
	int		founded;
	char	*cmd_path;

	founded = 0;
	paths = ft_split(ft_getenv(envp, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (!access(cmd_path, R_OK | X_OK))
			founded = 1;
		if (founded)
			break ;
		i++;
	}
	return (cmd_path);
}
