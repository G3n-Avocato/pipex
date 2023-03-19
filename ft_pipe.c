/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:59:44 by lamasson          #+#    #+#             */
/*   Updated: 2023/03/19 13:35:00 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_fork_exec(t_context context, int i, int fd_in, int *fd)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		perror("fork");
	if (pid == 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
		close(fd[0]);
		if (i == context.argc - 2)
		{
			close(fd[1]);
			fd[1] = ft_open_fd(context.argv[context.argc - 1], 1);
		}
		dup2(fd[1], 1);
		close(fd[1]);
		ft_exec_cmd(i, context);
		exit (0);
	}
	if (i == context.argc - 2)
		close(fd[0]);
	waitpid(pid, NULL, 0);
	return (0);
}

static int	check_in(t_context context)
{
	int	in;

	in = open(context.argv[1], O_RDONLY);
	if (in == -1)
		return (1);
	close(in);
	return (0);
}

static int	ft_pipe(t_context context, int i, int fd_in)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	if (fd_in == -1)
		fd_in = fd[0];
	if (check_in(context) == 1)
		close(fd[1]);
	ft_fork_exec(context, i, fd_in, fd);
	close(fd[1]);
	close(fd_in);
	return (fd[0]);
}

int	ft_call_pipe(t_context context, int i)
{
	int	fd_in;

	fd_in = ft_open_fd(context.argv[1], 0);
	while (i < context.argc - 2)
	{
		fd_in = ft_pipe(context, i, fd_in);
		i++;
	}
	ft_pipe(context, i, fd_in);
	close(fd_in);
	return (0);
}
