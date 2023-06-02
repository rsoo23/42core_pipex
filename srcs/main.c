/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:57 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/02 16:47:11 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

//     0     1    2     3       
// ./pipex file1 cmd1 cmd2 ... file2



void	create_pipes(int **pipefd, int cmd_num)
{
	int	i;

	i = -1;
	while (++i < cmd_num - 1)
	{
		if (pipe(pipefd[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

void	piping_proc(char ***cmd_list, int *fd_list, int cmd_num)
{
	int		pipefd[cmd_num - 1][2];
	pid_t	pids[cmd_num];
	int		i;
	char	*buf;

	i = 0;
	create_pipes(pipefd, cmd_num);
	while (i < cmd_num)
	{
		pids[i] = fork();
		if (pid[i] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid[0] == 0)
			read_from_infile(pipefd[0], fd_list[0], &buf);
		else if (pid[i] == 0)
			child_proc(pipefd[i], cmd_list, buf);
		else if (pid[cmd_num - 1] == 0)
			write_to_outfile(pipefd[cmd_num - 1], fd_list[1], &buf);
		i++;
	}
}

void	read_from_infile(int *pipefd, int fd1, char **buf)
{
	if (dup2(fd1, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	execute_cmd(); 
	exit(EXIT_SUCCESS);
}

void	write_to_outfile(int *pipefd, int fd2, char **buf)
{
	if (dup2(fd2, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	while (read(pipefd[0], &buf, 1) > 0)
		write(fd2, &buf, 1);
	close(pipefd[1]);
	exit(EXIT_SUCCESS);
}

/*
closes write end of pipe
redirect stdio to read end of pipe
*/
void	child_proc(int *pipefd)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	execve()
	close(pipefd[0]);
	exit(EXIT_SUCCESS);
}

/*
stdio -> child 1 -> write(1) PIPE 1 read(0) -> child 2 ... child n -> stdout 
*/

void	init_info(t_info *info)
{
	info->fd_in = 0;
	info->fd_out = 0;
	
}

void	get_fd(t_info *info, int ac, char **av)
{
	info->fd_in = open(av[1], O_RDONLY);
	info->fd_out = open(av[ac - 1], O_WRONLY);
	if (info->fd_in < 0 || info->fd_out < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
}

void	get_cmds(t_info *info, int ac, char **av)
{
	int		start;
	int		i;

	start = 2;
	i = 0;
	while (start < ac)
		cmd_list[i++] = ft_split(av[start++]);
	return (cmd_list);
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	init_info(info);
	get_fd(info, ac, av);
	get_cmd_list(info, ac, av);

	piping_proc(cmd_list, fd_list, cmd_num);
	// if (!ft_strncmp("here_doc", av[1], ft_strlen(av[1])))
	// {
	// }
	close(fd_list[0]);
	close(fd_list[1]);
	free(file_list);
}
