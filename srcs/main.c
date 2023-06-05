/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:57 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/05 02:46:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	init_info(info, ac);
	get_fd(info, ac, av);
	get_cmds(info, av);
	get_paths(info, envp);
	printf("%s\n", info->path_list[0]);
	printf("%s\n", info->path_list[1]);
	printf("%s\n", info->path_list[2]);
	printf("%s\n", info->path_list[3]);
	printf("%s\n", info->path_list[4]);
	
	parent_process(info);
	
	free_cmds(info->cmds);
	free_pipefd(info->pipefd);
	free_2d_array(info->path_list);
	free(info->pids);
	free(info);
}
