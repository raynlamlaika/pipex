/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:49:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/05 23:39:49 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	firstcmd(char **av, char **paths, int *pipfd)
{
	char	**cmd;
	char	*path;
	int		infile;

	infile = open(av[1], O_RDONLY);
	if(dup2(infile, STDIN_FILENO) == -1)
		return(close(infile), exit(1));
	if(dup2(pipfd[1], STDOUT_FILENO) == -1)
		return(close(infile),close(pipfd[1]), exit(1));
	cmd = split(av[2]);
	path = pick(paths, cmd[0]);
	if (!path)
	{
		clean_2(cmd);
		close(pipfd[1]);
		close(infile);
		perror("command nor found\n");
		exit(1);
	}
	close(infile);
	close(pipfd[0]);
	if (execve(path, cmd, NULL) == -1)
		perror("");
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
		return (write(1, "open failed 2\n", 14), 0);
	if ((dup2(pipfd[0], STDIN_FILENO) == -1))
		return (close(pipfd[0]),close(pipfd[1]), exit(1), 0);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (close(outfile),close(pipfd[1]), exit(1), 0);
	close(pipfd[1]);
	close(outfile);
	cmd = split(av[3]);
	path = pick(paths, cmd[0]);
	if (!path)
		return (perror("path not found\n"),clean_2(cmd), 0);
	if (execve(path, cmd, ev) == -1)
		perror("Execve failed\n");
	exit(1);
}

int	main(int ac, char**av, char**ev)
{
	int		pipfd[2];
	pid_t	pid;
	char	**paths;
	int		infile;

	if (ac != 5)
		exit(EXIT_FAILURE);
	infile = open(av[1], O_RDWR);
	if(infile == -1)
		perror(av[1]);
	if (pipe(pipfd) == -1)
		return (perror("pipe failed\n"), 0);
	paths = takepaths(ev, 0);
	if (!(paths))
		return (close(infile), close(pipfd[1]), close(pipfd[0]), 0);
	pid = fork();
	if (pid == -1)
		return (perror(""), close(infile), close(pipfd[1]), close(pipfd[0]), 0);
	if (pid == 0)
		firstcmd(av, paths, pipfd);
	else if (fork() == 0)
		last_cmmd(av, ev, paths, pipfd);
	close(pipfd[0]);
	close(pipfd[1]);
	wait(NULL);
	clean_2(paths);
	return (0);
}
