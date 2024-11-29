/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:42:13 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/29 07:11:28 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *prgm, char *msg, char *arg, int exit_code)
{
	write(2, prgm, ft_strlen(prgm));
	write(2, ": ", 2);
	write(2, msg, ft_strlen(msg));
	write(2, ": ", 2);
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
	exit(exit_code);
}
