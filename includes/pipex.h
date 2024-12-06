/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:32:32 by cauvray           #+#    #+#             */
/*   Updated: 2024/12/06 20:33:43 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"

/* Define : Messages */
# define WRONG_ARGS_MSG "infile cmd cmd outfile: wrong args"

// *** Env
char	*env_get_cmd_path(char **envp, char *cmd);

// *** Errors
void	free_tab(char **tab);
void	show_error(char *msg, int is_custom);

// *** File
int		open_file(char *file_name, int flags, int exit_on_error);

// *** Heredoc
void	init_heredoc(char *limiter);

// *** Pipe
void	dup2_close(int dup_from, int dup_to);
void	exec(char *str_cmd, char **envp);
int		pipe_cmd(char *str_cmd, char **envp);

#endif
