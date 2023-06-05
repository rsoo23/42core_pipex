/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 23:17:59 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/03 23:17:59 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
command path: /bin/(shell command)
*/
void	execute_cmd(t_info *info)
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (info->path_list[++i])
	{
		cmd_path = ft_strjoin(info->path_list[i], info->cmds[info->cmd_index][0]);
		if (access(cmd_path, X_OK) == 0)
		{
			if (execve(cmd_path, info->cmds[info->cmd_index], NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		free(cmd_path);
	}
	info->cmd_index++;
}

// reads from fd (infile) and writes it to the pipe
void	write_to_pipe(t_info *info, int fd, int i)
{
	char	buf;

	close(info->pipefd[i][0]);
	while (read(fd, &buf, 1) > 0)
		write(info->pipefd[i][1], &buf, 1);
	close(info->pipefd[i][1]);
}

// reads from pipe and writes to the fd (outfile)
void	read_from_pipe(t_info *info, int fd, int i)
{
	char	buf;

	close(info->pipefd[i][1]);
	while (read(info->pipefd[i][0], &buf, 1) > 0)
		write(fd, &buf, 1);
	close(info->pipefd[i][0]);
}

void	close_pipes(t_info *info)
{
	int	i;

	i = -1;
	while (info->pipefd[++i])
	{
		close(info->pipefd[i][0]);
		close(info->pipefd[i][1]);
	}
}
