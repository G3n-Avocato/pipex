/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 12:31:09 by lamasson          #+#    #+#             */
/*   Updated: 2023/02/24 15:00:41 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	open_here(void)
{
	int	fd_op;

	fd_op = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_op == -1)
	{
		perror(".here_doc");
		exit (1);
	}
	return (fd_op);
}

int	ft_rec_here(char *end)
{
	char	*line;
	int		fd_op;

	fd_op = open_here();
	while (1)
	{
		ft_printf(">");
		line = get_next_line(0);
		if (!line)
		{
			ft_printf("delimited by end-of-file (wanted `%s')\n", end);
			break ;
		}
		if (ft_strncmp(line, end, ft_strlen(end)) == 0)
			break ;
		ft_putstr_fd(line, fd_op);
		free(line);
	}
	free(line);
	close(fd_op);
	fd_op = open(".here_doc", O_RDONLY, 0644);
	return (fd_op);
}
