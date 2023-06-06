/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:57 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/06 11:31:28 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	pipe_handling(t_info *info, int ac, char **av, char **envp)
{
	get_fd(info, ac, av);
	get_cmds(info, av);
	get_paths(info, envp);
	piping(info, ac);
}

int	main(int ac, char **av, char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	if (ac >= 5)
	{
		init_info(info, ac);
		// if (!ft_strncmp(av[1], "here_doc", 8))
		// 	here_doc();
		// else
		pipe_handling(info, ac, av, envp);
		free_and_exit(info, NULL, EXIT_SUCCESS);
	}
	free(info);
}
