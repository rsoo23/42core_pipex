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

static void	execute_cmd(t_info *info)
{
	int		i;
	char	*cmd_path;
	char	**cmd;

	i = -1;
	cmd = ft_split(info->cmds[info->cmd_index], ' ');
	while (info->path_list[++i])
	{
		cmd_path = ft_strjoin(info->path_list[i], "/");
		cmd_path = ft_strjoin(cmd_path, cmd[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			if (execve(cmd_path, cmd, NULL) == -1)
			{
				free_2d_array(cmd);
				free(cmd_path);
				free_and_exit(info, "Execve Error");
			}
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

static void	child_process(t_info *info)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		free_and_exit(info, "Pipe Error");
	info->pid = fork();
	if (info->pid == -1)
		free_and_exit(info, "Fork Error");
	if (info->pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execute_cmd(info);
	}
	else if (info->pid > 0)
	{
		info->cmd_index++;
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(info->pid, NULL, 0);
	}
}

/*
fork():
child: opens the write end of pipe
parent: opens the read end of pipe and waits for child to end

piping:
1. connect the pipes first / do the redirection first

	initial: STDIN --> cmd 1 --> STDOUT
	result:   fdin --> cmd 1 --> pipefd[1]

2. execute cmd while parent waits
*/

void	piping(t_info *info, int ac)
{
	if (dup2(info->fd_in, STDIN_FILENO) == -1)
		free_and_exit(info, "Dup2 Error");
	while (ac-- > 4)
		child_process(info);
	if (dup2(info->fd_out, STDOUT_FILENO) == -1)
		free_and_exit(info, "Dup2 Error");
	execute_cmd(info);
}
