/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:49:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/04 19:20:29 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	firstcmd(char **av, char **paths, int *pipfd)
{
	char	**cmd;
	char	*path;
	int		infile;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		return ;
	if (dup2(infile, STDIN_FILENO) == -1 || \
	dup2(pipfd[1], STDOUT_FILENO) == -1)
		return ;
	cmd = split(av[2]);
	path = pick(paths, cmd[0]);
	close(infile);
	close(pipfd[0]);
	if (!path)
		return ;
	execve(path, cmd, NULL);
	return ;
}

int	last_cmmd(char**av, char **ev, char**paths, int *pipfd)
{
	int		outfile;
	char	**cmd;
	char	*path;

	outfile = open(av[4], O_CREAT | O_TRUNC | O_APPEND | O_RDWR, 0644);
	if (outfile == -1)
		return (write(1, "open fAiled 1\n", 15), 0);
	if ((dup2(pipfd[0], STDIN_FILENO) == -1) || \
	(dup2(outfile, STDOUT_FILENO) == -1))
		return (0);
	close(pipfd[1]);
	close(outfile);
	cmd = split(av[3]);
	path = pick(paths, cmd[0]);
	if (!path)
		return (write(2, "path | command not reached\n", 27), 0);
	execve(path, cmd, ev);
	exit(0);
}

int	main(int ac, char**av, char**ev)
{
	int		pipfd[2];
	pid_t	pid;
	char	**paths;

	if (ac != 5)
		exit(EXIT_FAILURE);
	if (pipe(pipfd) == -1)
		return (0);
	paths = takepaths(ev, 0);
	if (!(paths))
		return (0);
	pid = fork();
	if (pid == -1)
		return (write(2, "fork failed\n", 13), 0);
	if (pid == 0)
		firstcmd(av, paths, pipfd);
	else if (fork() == 0)
		last_cmmd(av, ev, paths, pipfd);
	close(pipfd[0]);
	close(pipfd[1]);
	wait(NULL);
	wait(NULL);
	clean_2(paths);
	return (0);
}
