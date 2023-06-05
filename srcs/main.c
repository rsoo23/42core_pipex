/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:57 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/05 23:44:15 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (ac >= 5)
	{
		init_info(info, ac);
		get_fd(info, ac, av);
		get_cmds(info, av);
		get_paths(info, envp);
		piping(info, ac);
		free_2d_array(info->cmds);
		free_2d_array(info->path_list);
	}
	free(info);
}
