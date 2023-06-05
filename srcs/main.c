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

int	main(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	init_info(info, ac);
	get_fd(info, ac, av);
	get_cmds(info, av);
	
	parent_process(info);
	
	free_cmds(info->cmds);
	free_pipefd(info->pipefd);
	free(info->pids);
	free(info);
}
