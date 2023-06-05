/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:13 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/04 00:17:21 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"

typedef struct s_info
{
	int		fd_in;
	int		fd_out;
	int		cmd_num;
	int		pipe_num;
	char	***cmds;
	int		**pipefd;
	pid_t	*pids;
	char	*cmd_path;
	int		cmd_index;
	int		pipe_index;
}	t_info;

// parsing_utils.c
void	init_info(t_info *info, int ac);
void    free_cmds(char ***cmds);
void	free_pipefd(int	**pipefd);
void	get_fd(t_info *info, int ac, char **av);
void	get_cmds(t_info *info, char **av);

// piping.c
void	parent_process(t_info *info);

// utils_1.c
void	execute_cmd(t_info *info);
void	write_to_pipe(t_info *info, int fd, int i);
void	read_from_pipe(t_info *info, int fd, int i);
void	close_pipes(t_info *info);

#endif
