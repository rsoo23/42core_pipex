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
	info->cmds = NULL;
	info->path_list = NULL;
	info->cmd_index = 0;
	info->pipe_index = 0;
}

void	get_fd(t_info *info, int ac, char **av)
{
	info->fd_in = open(av[1], O_RDONLY);
	info->fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (info->fd_in < 0)
		free_and_exit(info, "Infile Error", EXIT_FAILURE);
	if (info->fd_out < 0)
		free_and_exit(info, "Outfile Error", EXIT_FAILURE);
}

//     0     1    2     3       
// ./pipex file1 cmd1 cmd2 ... file2
void	get_cmds(t_info *info, char **av)
{
	int	i;

	i = -1;
	info->cmds = malloc(sizeof(char *) * (info->cmd_num + 1));
	if (!info->cmds)
		return ;
	while (++i < info->cmd_num)
		info->cmds[i] = ft_strdup(av[i + 2]);
	info->cmds[i] = 0;
}

void	get_paths(t_info *info, char **envp)
{
	int		i;
	char	*path_str;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	path_str = ft_substr(envp[i], 5, 1024);
	info->path_list = ft_split(path_str, ':');
	free(path_str);
}
