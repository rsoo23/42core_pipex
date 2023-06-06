/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:57 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/06 14:54:28 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	init_info(t_info *info, int ac)
{
	info->fd_in = 0;
	info->fd_out = 0;
	info->cmd_num = ac - 3;
	info->pipe_num = info->cmd_num - 1;
	info->cmds = NULL;
	info->path_list = NULL;
	info->cmd_index = 0;
	info->pipe_index = 0;
}

static void	pipe_handling(t_info *info, int ac, char **av)
{
	get_files_fd(info, ac, av);
	get_cmds(info, av);
	piping(info, ac);
}

static void	here_doc(t_info *info, int ac, char **av)
{
	char	*limiter;

	limiter = ft_strjoin(av[2], "\n");
	get_heredoc_file_fd(info, ac, av);
	get_heredoc_cmds(info, av);
	here_doc_child_process(info, limiter);
	free(limiter);
	if (dup2(info->fd_out, STDOUT_FILENO) == -1)
		free_and_exit(info, "Dup2 Error", EXIT_FAILURE);
	execute_cmd(info);
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
		get_paths(info, envp);
		if (!ft_strncmp(av[1], "here_doc", 8))
			here_doc(info, ac, av);
		else
			pipe_handling(info, ac, av);
		free_and_exit(info, NULL, EXIT_SUCCESS);
	}
	free(info);
	info = NULL;
}
