/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:49:29 by lamasson          #+#    #+#             */
/*   Updated: 2023/03/19 15:26:28 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_cat_mod_pipe(char *s1, char *s2, char *s3)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	s3[i] = '/';
	i++;
	while (s2[y] != '\0')
	{
		s3[i] = s2[y];
		i++;
		y++;
	}
	s3[i] = '\0';
}

static char	*ft_strjoin_pipe(char *s1, char *s2)
{
	char	*s3;
	int		size_s3;

	if (!s1)
		return (NULL);
	size_s3 = ft_strlen((char *) s1) + ft_strlen((char *) s2) + 1;
	s3 = malloc(sizeof(char) * (size_s3 + 1));
	if (!s3)
		return (NULL);
	ft_cat_mod_pipe(s1, s2, s3);
	free(s1);
	return (s3);
}

static char	*ft_access_path(char **tab, char *cmd)
{
	int		i;
	int		res;
	char	*path;

	i = 0;
	res = -2;
	while (tab[i] != NULL)
	{
		res = access(tab[i], X_OK);
		if (res == 0)
		{
			path = ft_strdup(tab[i]);
			return (path);
		}
		i++;
	}
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	free(cmd);
	ft_free_tab(tab);
	close(1);
	close(0);
	exit (1);
}

char	*ft_get_path(char *cmd, char *env[])
{
	int		i;
	int		size;
	char	*way_path;
	char	**tab;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (env[i] != NULL && ft_strncmp(env[i], "PATH", 4) != 0)
		i++;
	if (env[i] == NULL)
		return (env[i]);
	size = ft_strlen(env[i]);
	way_path = ft_substr(env[i], 5, size);
	tab = ft_split(way_path, ':');
	free(way_path);
	i = -1;
	while (tab[++i] != NULL)
		tab[i] = ft_strjoin_pipe(tab[i], cmd);
	way_path = NULL;
	way_path = ft_access_path(tab, cmd);
	ft_free_tab(tab);
	return (way_path);
}
