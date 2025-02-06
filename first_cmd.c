/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:41:36 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/06 13:48:23 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_command(char **av, char **paths, int *pipfd)
{
	char	**cmd;
	char	*path;
	int		infile;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		exit(1);
	if (dup2(infile, STDIN_FILENO) == -1 || \
		dup2(pipfd[1], STDOUT_FILENO) == -1)
		return ;
	cmd = ft_split(av[2], ' ');
	path = pick(paths, cmd[0]);
	close(pipfd[0]);
	if (!path)
		return ;
	execve(path, cmd, NULL);
	exit(1);
}
