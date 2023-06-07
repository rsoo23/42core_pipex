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

void	execute_cmd(t_info *info)
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
		if (access(cmd_path, X_OK) == 0 && execve(cmd_path, cmd, NULL) == -1)
		{
			free_2d_array(cmd);
			free(cmd_path);
			free_and_exit(info, "Execve Error", EXIT_FAILURE);
		}
	}
	free(cmd_path);
	free_2d_array(cmd);
	free_and_exit(info, "Command not found", EXIT_FAILURE);
}

/*
dup2(old, new);
- lets say the file has 3 as its fd, it duplicates the fd so that
  the new one also represents the fd of the file
- below: fd_in and 0 represents the file fd
- redirect STDIN to the file fd
*/

void	child_process(t_info *info)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		free_and_exit(info, "Pipe Error", EXIT_FAILURE);
	info->pid = fork();
	if (info->pid == -1)
		free_and_exit(info, "Fork Error", EXIT_FAILURE);
	if (info->pid == 0)
	{
		close(pipefd[READ_END]);
		if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1)
			free_and_exit(info, "Dup2 Error", EXIT_FAILURE);
		execute_cmd(info);
	}
	else if (info->pid > 0)
	{
		if (waitpid(info->pid, NULL, 0) == -1)
			free_and_exit(info, "Waitpid Error", EXIT_FAILURE);
		info->cmd_index++;
		close(pipefd[WRITE_END]);
		if (dup2(pipefd[READ_END], STDIN_FILENO) == -1)
			free_and_exit(info, "Dup2 Error", EXIT_FAILURE);
	}
}

/*
fork():
child: opens the write end of pipe
parent: opens the read end of pipe and waits for child to end

piping:
1. connect the pipes first / do the redirection first

	initial: STDIN --> cmd 1 --> STDOUT
	result:   fdin --> cmd 1 --> pipefd[WRITE_END]

2. execute cmd while parent waits
*/

void	piping(t_info *info, int ac)
{
	if (dup2(info->fd_in, STDIN_FILENO) == -1)
		free_and_exit(info, "Dup2 Error", EXIT_FAILURE);
	while (ac-- > 4)
		child_process(info);
	if (dup2(info->fd_out, STDOUT_FILENO) == -1)
		free_and_exit(info, "Dup2 Error", EXIT_FAILURE);
	execute_cmd(info);
}
