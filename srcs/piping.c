/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:57:12 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/03 21:57:12 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	create_pipes(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->pipe_num)
	{
		if (pipe(info->pipefd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

/*
dup2(old, new);
- lets say the file has 3 as its fd, it duplicates the fd so that
  the new one also represents the fd of the file
- below: fd_in and 0 represents the file fd
- redirect STDIN to the file fd
*/
static void	infile_to_pipe(t_info *info)
{
	if (dup2(info->fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	execute_cmd(info);
	write_to_pipe(info, info->fd_in, info->pipe_index);
}

static void	pipe_to_outfile(t_info *info)
{
	if (dup2(info->fd_out, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	while (read(pipefd[0], &buf, 1) > 0)
		write(fd2, &buf, 1);
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

void	parent_process(t_info *info)
{
	int		i;

	i = -1;
	create_pipes(info);
	while (++i < info->cmd_num)
	{
		info->pids[i] = fork();
		if (info->pids[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (info->pids[0] == 0)
			infile_to_pipe(info);
		else if (info->pids[info->pipe_num - 1] == 0)
			pipe_to_outfile(info);
		else
			execute_cmd(info);
		piping_process(info);
	}
}

/*
          INFILE -> child 1: execve -> write to pipe 1
read from pipe 1 -> child 2: execve -> write to pipe 2
read from pipe 2 -> child 2: execve -> write to pipe 3
read from pipe 3 -> child 3: execve -> OUTFILE 
*/
