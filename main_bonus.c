/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:47:41 by lamasson          #+#    #+#             */
/*   Updated: 2023/03/16 16:48:27 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_check_fdin(t_context context)
{
	int	fd_in;

	if (ft_strncmp(context.argv[1], "here_doc", 8) == 0)
		return (3);
	fd_in = open(context.argv[1], O_RDONLY);
	if (fd_in == -1)
		return (3);
	else
		close(fd_in);
	return (2);
}

static int	ft_check_fdout(t_context context)
{
	int	fd_out;

	fd_out = open(context.argv[context.argc - 1], O_RDWR);
	if (fd_out == -1)
	{
		fd_out = open(context.argv[context.argc - 1], O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			perror(context.argv[context.argc - 1]);
			exit (1);
		}
	}
	close (fd_out);
	return (1);
}

int	main(int argc, char **argv, char *env[])
{
	t_context	context;
	int			i;

	context.argc = argc;
	context.argv = argv;
	context.env = env;
	if (argc < 5)
	{
		ft_putendl_fd("command not found, to few arguments", 1);
		return (1);
	}
	i = ft_check_fdin(context);
	ft_check_fdout(context);
	ft_call_pipe(context, i);
	unlink(".here_doc");
	return (0);
}
