/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_last_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:41:36 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/30 17:57:48 by rlamlaik         ###   ########.fr       */
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
		return ;
	if (dup2(infile, STDIN_FILENO) == -1 || \
	    dup2(pipfd[1], STDOUT_FILENO) == -1)// FD for write
		return ;
	cmd = ft_split(av[2], ' ');
	path = pick(paths, cmd[0]);
	close(pipfd[0]);
	if (!path)
		return ;
	execve(path, cmd, NULL);
	exit(1);
	return ;
}

int	last_commmand(int ac, char**av,char **ev, char** paths, int *pipfd)
{
	int		outfile;
	char	**cmd;
	char	*path;

	outfile = open(av[(ac - 1)], O_CREAT | O_TRUNC | O_APPEND | O_RDWR, 0644);
	if (outfile == -1)
		return (write(1, "open fAiled 1\n", 15), 0);
	if ((dup2(pipfd[0], STDIN_FILENO) == -1) || \
	(dup2(outfile, STDOUT_FILENO) == -1))
		return (0);
	close(pipfd[1]);
	close(outfile);
	cmd = ft_split(av[3], ' ');
	path = pick(paths, cmd[0]);
	if (!path)
		return (write(2, "path | command not reached\n", 27), 0);
	execve(path, cmd, ev);
	exit(0);
}