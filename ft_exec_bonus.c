/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:43:01 by lamasson          #+#    #+#             */
/*   Updated: 2023/03/16 17:24:15 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_open_fd(t_context context, char *fd, int std)
{
	int	fd_op;

	fd_op = -2;
	if (std == 0 && ft_strncmp(fd, "here_doc", 8) == 0)
		fd_op = ft_rec_here(context.argv[2]);
	else if (std == 0)
		fd_op = open(fd, O_RDONLY);
	else if (std == 1 && ft_strncmp(context.argv[1], "here_doc", 8) == 0)
		fd_op = open(fd, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (std == 1)
		fd_op = open(fd, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd_op == -1)
	{
		perror(fd);
		return (-1);
	}
	return (fd_op);
}

char	*ft_parse_cmd(char *str)
{
	int		i;
	char	*cmd;

	i = 0;
	if (!str)
	{
		ft_putendl_fd("command not found. Empty", 2);
		exit(1);
	}
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			cmd = ft_substr(str, 0, i);
			return (cmd);
		}
		i++;
	}
	cmd = ft_strdup(str);
	return (cmd);
}

int	ft_exec_cmd(int i, t_context context)
{
	int		res;
	char	*cmd;
	char	*path;
	char	**tab_arg;

	cmd = ft_parse_cmd(context.argv[i]);
	path = ft_get_path(cmd, context.env);
	free(cmd);
	if (path == NULL)
	{
		perror(context.argv[i]);
		free(path);
		return (1);
	}
	tab_arg = ft_split(context.argv[i], ' ');
	res = execve(path, tab_arg, context.env);
	if (res == -1)
	{
		free(path);
		ft_free_tab(tab_arg);
		perror("execve");
		exit (1);
	}
	return (0);
}
