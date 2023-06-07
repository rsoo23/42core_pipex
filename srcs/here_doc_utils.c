/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:52:26 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/07 13:39:20 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_heredoc_file_fd(t_info *info, int ac, char **av)
{
	info->fd_out = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (info->fd_out < 0)
		free_and_exit(info, "Outfile Error", EXIT_FAILURE);
}

void	get_heredoc_cmds(t_info *info, char **av)
{	
	int	i;

	i = -1;
	info->cmds = malloc(sizeof(char *) * 3);
	if (!info->cmds)
		return ;
	while (++i < 2)
		info->cmds[i] = ft_strdup(av[i + 3]);
	info->cmds[i] = 0;
}

/*
here_doc
1. use gnl on the stdin
2. write the output into the pipe
3. execute the command
4. redirect stdin to the read end of the pipe
5. append to the file
*/

static void	here_doc_gnl(t_info *info, int *pipefd)
{
	char	*str;

	str = get_next_line(STDIN_FILENO);
	while (ft_strncmp(str, info->limiter, ft_strlen(info->limiter)))
	{
		write(pipefd[WRITE_END], str, ft_strlen(str));
		free(str);
		str = get_next_line(STDIN_FILENO);
	}
	free(str);
	exit(EXIT_SUCCESS);
}

void	here_doc_child_process(t_info *info)
{
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		free_and_exit(info, "pipe", EXIT_FAILURE);
	info->pid = fork();
	if (info->pid == -1)
		free_and_exit(info, "fork", EXIT_FAILURE);
	else if (info->pid == 0)
	{
		close(pipefd[READ_END]);
		here_doc_gnl(info, pipefd);
	}
	else if (info->pid > 0)
	{
		if (waitpid(info->pid, NULL, 0) == -1)
			free_and_exit(info, "Waitpid Error", EXIT_FAILURE);
		close(pipefd[WRITE_END]);
		if (dup2(pipefd[READ_END], STDIN_FILENO) == -1)
			free_and_exit(info, "Dup2 Error", EXIT_FAILURE);
	}
}
