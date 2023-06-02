/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsoo <rsoo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:40:13 by rsoo              #+#    #+#             */
/*   Updated: 2023/06/02 16:46:49 by rsoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

typedef struct s_cmds
{
	char			**cmd;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_info
{
	int		fd_in;
	int		fd_out;
	t_cmds	*cmds; 
}	t_info;

#endif
