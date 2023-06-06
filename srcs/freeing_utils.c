/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 02:11:23 by codespace         #+#    #+#             */
/*   Updated: 2023/06/06 08:53:10 by rsoo             ###   ########.fr       */
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

void	free_and_exit(t_info *info, const char *str)
{
	perror(str);
	if (info->cmds)
		free_2d_array(info->cmds);
	if (info->path_list)
		free_2d_array(info->path_list);
	free(info);
	exit(EXIT_FAILURE);
}
