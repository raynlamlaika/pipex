/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:13:22 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/04 17:33:23 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_command(int ac, char **av, char**path)
{
	int		i;
	char	*cmd;
	char	**cmm;

	i = ac - 2;
	while (i > 1)
	{
		cmm = split(av[i]);
		cmd = pick(path, cmm[0]);
		if (!cmd)
		{
			write(2, "cmmand not fond\n", 16);
			exit(1);
		}
		i--;
	}
}

int	executing(int prev_pipe, char**av, int j, char**paths, int outfile)
{
	char	**command;
	char	*path;

	if (fork() == 0)
	{
		if ((dup2(prev_pipe, STDIN_FILENO) == -1) || \
			(dup2(outfile, STDOUT_FILENO) == -1))
			return (perror("dup2 failed"), 0);
		close(prev_pipe);
		close(outfile);
		command = split(av[j]);
		path = pick(paths, command[0]);
		if (execve(path, command, NULL) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	return (0);
}

int	main(int ac, char**av, char**ev)
{
	int		pipefd[2];
	char	**paths;
	int		i;
	int		prev_pipe;
	int		outfile;
	int		infile;
	pid_t	pid;

	if (ac < 5)
		return (write(2, "args not enough\n", 16), 0);
	if (pipe(pipefd) == -1)
		return (write(2, "pipe failed\n", 12), 0);
	paths = takepaths(ev);
	if (!paths)
		return (write(2, "path error\n", 12), 0);
	infile = open(av[1], O_RDONLY);
	outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (infile == -1 || outfile == -1)
		return (write(2, "file error\n", 12), 0);
	i = 1;
	while (i < (ac - 2))
	{
		if (pipe(pipefd) == -1)
			return (write(2, "pipe failed\n", 12), 0);
		pid = fork();
		if (pid == -1)
			return (write(2, "fork failed\n", 12), 0);
		if (pid == 0)
		{
			if (i == 1)
				first_command(av, paths, pipefd);
			else
				executing(prev_pipe, av, i, paths, pipefd[1]);
			close(pipefd[0]);
			exit(0);
		}
		else
		{
			close(pipefd[1]);
			if (i > 1)
				close(prev_pipe);
			prev_pipe = pipefd[0];
		}
		i++;
	}
	executing(prev_pipe, av, i, paths, outfile);
	close(prev_pipe);
	close(outfile);
	while (wait(NULL) > 0)
		;
	return (0);
}
