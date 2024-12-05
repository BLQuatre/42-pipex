/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 05:49:15 by cauvray           #+#    #+#             */
/*   Updated: 2024/12/04 20:48:07 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*env_get(char **envp, char *env_name)
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

static char **env_get_splitted_path(char **envp)
{
	char	**paths;
	char	*env_path;

	env_path = env_get(envp, "PATH");
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

char	*env_get_cmd_path(char **envp, char *cmd)
{
	char	**paths;
	int		i;
	char	*path;
	char	*cmd_path;

	paths = env_get_splitted_path(envp);
	if (!paths)
		return (NULL);
	cmd_path = ft_strdup("");
	i = 0;
	while (paths[i])
	{
		free(cmd_path);
		path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (access(cmd_path, R_OK | X_OK) == 0)
			return (free_tab(paths), cmd_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}
