/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 02:11:23 by codespace         #+#    #+#             */
/*   Updated: 2023/06/05 02:36:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_cmds(char ***cmds)
{
    int i;
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

void	free_pipefd(int	**pipefd)
{
	int	i;

	i = -1;
	while (pipefd[++i])
		free(pipefd[i]);
	free(pipefd);
}

void	free_2d_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}
