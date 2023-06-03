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
	info->cmd_path = ft_strjoin("/bin/", info->cmds[info->cmd_index][0]);
	if (access(info->cmd_path, X_OK) == 0)
	{
		if (execve(info->cmd_path, info->cmds[info->cmd_index], NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	info->cmd_index++;
	free(info->cmd_path);
}

void	write_to_pipe(t_info *info, int read_fd, int i)
{
	char	buf;

	close(info->pipefd[i][0]);
	while (read(read_fd, &buf, 1) > 0)
		write(info->pipefd[i][1], &buf, 1);
	close(info->pipefd[i][1]);
}
