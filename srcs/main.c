/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:57 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/04 00:14:20 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
closes write end of pipe
redirect stdio to read end of pipe
*/
void	child_proc(int *pipefd)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	execve()
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	init_info(info, ac);
	get_fd(info, ac, av);
	get_cmds(info, av);
	
	parent_process(info);
	
	free_cmds(info->cmds);
	free(info);
}
