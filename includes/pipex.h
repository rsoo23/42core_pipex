/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:13 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/06 08:07:19 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

typedef struct s_info
{
	int		fd_in;
	int		fd_out;
	int		cmd_num;
	int		pipe_num;
	char	**cmds;
	pid_t	pid;
	int		cmd_index;
	int		pipe_index;
	char	**path_list;
}	t_info;

// parsing_utils.c
void	init_info(t_info *info, int ac);
void	get_fd(t_info *info, int ac, char **av);
void	get_cmds(t_info *info, char **av);
void	get_paths(t_info *info, char **envp);

// freeing_utils.c
void	free_2d_array(char **arr);
void	free_and_exit(t_info *info, const char *str);

// piping.c
void	piping(t_info *info, int ac);

#endif
