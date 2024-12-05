/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:32:32 by cauvray           #+#    #+#             */
/*   Updated: 2024/12/05 02:56:25 by cauvray          ###   ########.fr       */
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
# define CMD_NOT_FOUND_MSG "command not found"
# define WRONG_ARGS_MSG "infile cmd cmd outfile: wrong args"
# define WRONG_ARGS_HD_MSG "here_doc limiter cmd cmd outfile: wrong args"
# define PERMISSION_DENIED "permission denied"

# define WRONG_ARGS_NB_MSG "[MAIN] Wrong number of arguments"
# define NOT_ENOUGH_PERMS "[MAIN] Not enough permissions to open/read the file"
# define WRONG_FILE_EXT_MSG "[MAIN] Wrong file extension, map must be in .ber"
# define MALLOC_FAILED_MSG "[MAIN] Malloc failed"

# define NO_MAP_MSG "[MAP] Map not found"
# define INVALID_MAP_MSG "[MAP] Invalid map"
# define INVALID_MAP_PATH_MSG "[MAP] Invalid map path"
# define INVALID_CHAR_MSG "[MAP] Invalid character in map"
# define INVALID_LEN_MSG "[MAP] Invalid line length"
# define INVALID_BORDER_MSG "[MAP] Invalid border"
# define MISSING_COMPONENT_MSG "[MAP] Missing component"
# define DUPLICATE_PLAYER_START_MSG "[MAP] Duplicate player start"
# define DUPLICATE_EXIT_MSG "[MAP] Duplicate exit"

// *** Env
char	*env_get_cmd_path(char **envp, char *cmd);

// *** Errors
void	free_tab(char **tab);
void	show_error(char *msg, int is_custom);

// *** File
int		open_file(char *file_name, int flags);

// *** Heredoc
void	init_heredoc(char *limiter);

// *** Pipe
void	dup2_close(int dup_from, int dup_to);
void	exec(char *str_cmd, char **envp);
int		pipe_cmd(char *str_cmd, char **envp);

#endif
