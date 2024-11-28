/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cauvray <cauvray@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:32:32 by cauvray           #+#    #+#             */
/*   Updated: 2024/11/28 04:39:36 by cauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

/* Define : Messages */
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

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}	t_cmd;

typedef struct s_pipex
{
	int		here_doc;
	int		is_invalid_infile;
	t_list	*cmds;
}	t_pipex;

int		ft_tab_len(char **tab);

/*** ERRORS */
void	quit(int exit_code, char *msg, t_pipex *pipex);

/*** CMDS */
t_cmd	*ft_cmd_get(char *str);
void	ft_cmd_free(t_cmd *cmd);

/*** DEBUG */
void	print_cmd(t_cmd *cmd);
void	print_params(int argc, char **argv);

#endif
