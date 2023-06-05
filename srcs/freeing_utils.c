/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 02:11:23 by codespace         #+#    #+#             */
/*   Updated: 2023/06/05 20:23:10 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_cmds(char ***cmds)
{
	int	i;
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

void	free_2d_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_and_exit(t_info *info)
{
	perror("Error");
	free_cmds(info->cmds);
	free_2d_array(info->path_list);
	free(info);
	exit(EXIT_FAILURE);
}
