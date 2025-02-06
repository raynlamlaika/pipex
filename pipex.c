/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:49:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/06 14:08:02 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	firstcmd(char **av, char **paths, int *pipfd)
{
	char	**cmd;
	char	*path;
	int		infile;

	infile = open(av[1], O_RDONLY);
	if (dup2(infile, STDIN_FILENO) == -1)
		return (close(infile), exit(1));
	if (dup2(pipfd[1], STDOUT_FILENO) == -1)
		return (close(infile), close(pipfd[1]), exit(1));
	cmd = split(av[2]);
	path = pick(paths, cmd[0]);
	if (!path)
	{
		clean_2(cmd);
		close(pipfd[1]);
		close(infile);
		write(2, "pipex: command not found\n", 25);
		exit(1);
	}
	close(infile);
	close(pipfd[0]);
	if (execve(path, cmd, NULL) == -1)
		perror("pipex");
	exit(1);
	return ;
}

int	last_cmmd(char**av, char **ev, char**paths, int *pipfd)
{
	int		outfile;
	char	**cmd;
	char	*path;

	outfile = open(av[4], O_CREAT | O_TRUNC | O_APPEND | O_RDWR, 0644);
	if (outfile == -1)
		return (perror("pipex"), 0);
	if ((dup2(pipfd[0], STDIN_FILENO) == -1))
		return (close(pipfd[0]), close(pipfd[1]), exit(1), 0);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (close(outfile), close(pipfd[1]), exit(1), 0);
	close(pipfd[1]);
	close(outfile);
	cmd = split(av[3]);
	path = pick(paths, cmd[0]);
	if (!path)
		return (perror("pipex"), clean_2(cmd), 0);
	if (execve(path, cmd, ev) == -1)
		perror("pipex");
	exit(1);
}

int	main(int ac, char**av, char**ev)
{
	int		pfd[2];
	pid_t	pid;
	char	**paths;
	int		inf;

	if (ac != 5)
		exit(EXIT_FAILURE);
	inf = open(av[1], O_RDWR);
	if (inf == -1)
		perror("pipex");
	if (pipe(pfd) == -1)
		return (perror("pipex"), 0);
	paths = takepaths(ev, 0);
	if (!(paths))
		return (close(inf), close(pfd[1]), close(pfd[0]), 0);
	pid = fork();
	if (pid == -1)
		return (perror("pipex"), close(inf), close(pfd[1]), close(pfd[0]), 0);
	if (pid == 0)
		firstcmd(av, paths, pfd);
	else if (fork() == 0)
		last_cmmd(av, ev, paths, pfd);
	close(pfd[0]);
	close(pfd[1]);
	return (wait(NULL), clean_2(paths), 0);
}
