/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:32:32 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/26 23:16:43 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

# define MALLOC_FAILED "Malloc failed"

typedef struct s_cmd
{
	char	*cmd;
	char	**params;
}	t_cmd;

int		ft_tab_len(char **tab);

/*** ERRORS */
void	quit(int exit_code, char *msg);

/*** CMDS */
t_cmd	*ft_cmd_get(char *str);
void	ft_cmd_free(t_cmd *cmd);

/*** DEBUG */
void	print_cmd(t_cmd *cmd);
void	print_params(int argc, char **argv);

#endif
