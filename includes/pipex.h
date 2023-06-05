/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:13 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/05 02:45:19 by codespace        ###   ########.fr       */
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
void    free_cmds(char ***cmds);
void	free_pipefd(int	**pipefd);
void	free_2d_array(char **arr);

// piping.c
void	parent_process(t_info *info);

// piping_utils.c
void	execute_cmd(t_info *info);
void	write_to_pipe(t_info *info, int fd, int i);
void	read_from_pipe(t_info *info, int fd, int i);
void	close_pipes(t_info *info);

#endif
