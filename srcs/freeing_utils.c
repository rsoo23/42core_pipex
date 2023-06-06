/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 02:11:23 by codespace         #+#    #+#             */
/*   Updated: 2023/06/06 15:06:03 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_2d_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void	free_and_exit(t_info *info, const char *str, int status)
{
	if (status != 0)
		perror(str);
	if (info->cmds)
	{
		free_2d_array(info->cmds);
		info->cmds = NULL;
	}
	if (info->path_list)
	{
		free_2d_array(info->path_list);
		info->path_list = NULL;
	}
	free(info);
	info = NULL;
	exit(status);
}
