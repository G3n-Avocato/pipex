/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamasson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:55:03 by lamasson          #+#    #+#             */
/*   Updated: 2023/03/16 17:41:59 by lamasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_context{
	int		argc;
	char	**argv;
	char	**env;
}t_context;

char	*ft_get_path(char *cmd, char *env[]);
int		ft_call_pipe(t_context context, int i);
int		ft_exec_cmd(int i, t_context context);
char	*ft_parse_cmd(char *str);
int		ft_open_fd(t_context context, char *fd, int std);
int		ft_rec_here(char *end);

#endif
