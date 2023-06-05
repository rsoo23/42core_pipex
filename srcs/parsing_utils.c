/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:33:16 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/03 21:33:16 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_info(t_info *info, int ac)
{
	info->fd_in = 0;
	info->fd_out = 0;
	info->cmd_num = ac - 3;
	info->pipe_num = info->cmd_num - 1;
    info->cmds = malloc(sizeof(char **) * info->cmd_num);
	info->pipefd = malloc(sizeof(int *) * info->pipe_num);
	info->pids = malloc(sizeof(pid_t) * info->cmd_num);
	info->cmd_index = 0;
	info->pipe_index = 0;
}

void	free_cmds(char ***cmds)
{
    int i;
	int	j;

    i = -1;
    while (cmds[++i])
	{
		j = -1;
		while (cmds[i][++j])
			free(cmds[i][j]);
        free(cmds[i]);
	}
    free(cmds);
}

void	free_pipefd(int	**pipefd)
{
	int	i;

	i = -1;
	while (pipefd[++i])
		free(pipefd[i]);
	free(pipefd);
}

void	get_fd(t_info *info, int ac, char **av)
{
	info->fd_in = open(av[1], O_RDONLY);
	info->fd_out = open(av[ac - 1], O_WRONLY);
	if (info->fd_in < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	if (info->fd_out < 0)
	{
		info->fd_out = open(av[ac - 1], O_CREAT | O_WRONLY);
		if (info->fd_out < 0)
		{
			perror("Error creating outfile");
			exit(EXIT_FAILURE);
		}
	}
}

//     0     1    2     3       
// ./pipex file1 cmd1 cmd2 ... file2
void	get_cmds(t_info *info, char **av)
{
    int i;

    i = -1;
    while (++i < info->cmd_num)
        info->cmds[i] = ft_split(av[i + 2], ' ');
}
