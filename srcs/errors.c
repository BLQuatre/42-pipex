/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:42:13 by cauvray           #+#    #+#             */
/*   Updated: 2024/12/04 21:32:36 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	show_error(char *msg, int is_custom)
{
	ft_putstr_fd("bash: ", 2);
	if (is_custom)
		ft_putendl_fd(msg, 2);
	else
		perror(msg);
}
