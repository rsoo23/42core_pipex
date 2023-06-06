/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:52:26 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/06 17:35:45 by rsoo             ###   ########.fr       */
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
	if (!str)
		return ;
	printf("hi: %d\n", ft_strncmp(str, info->limiter, ft_strlen(info->limiter)) != 0);
	while (ft_strncmp(str, info->limiter, ft_strlen(info->limiter)) != 0)
	{
		write(pipefd[1], str, ft_strlen(str));
		free(str);
		str = get_next_line(STDIN_FILENO);
	}
	free(str);
}

void	here_doc_child_process(t_info *info)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		free_and_exit(info, "Pipe Error", EXIT_FAILURE);
	info->pid = fork();
	if (info->pid == -1)
		free_and_exit(info, "Fork Error", EXIT_FAILURE);
	if (info->pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			free_and_exit(info, "Dup2 Error", EXIT_FAILURE);
		here_doc_gnl(info, pipefd);
		execute_cmd(info);
	}
	else if (info->pid > 0)
	{
		waitpid(info->pid, NULL, 0);
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			free_and_exit(info, "Dup2 Error", EXIT_FAILURE);
	}
}
