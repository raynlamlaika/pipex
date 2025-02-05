/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:13:22 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/05 23:11:45 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	executing(int prev_pipe, char**av, int j, char**paths, int outfile)
{
	char	**command;
	char	*path;

	if (fork() == 0)
	{
		if (dup2(prev_pipe, STDIN_FILENO) == -1)
			return (perror("pipex"), 0);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			return (perror("pipex"), close(prev_pipe), 0);
		close(prev_pipe);
		close(outfile);
		command = split(av[j]);
		if (!command)
			return(clean_2(command), 0);
		path = pick(paths, command[0]);
		if (execve(path, command, NULL) == -1)
		{
			perror("execve failed");
			exit(1);
		}
	}
	return (0);
}


int check(char **ev, int ac)
{
	if (ac < 5)
		return (perror("argemment not enough"), 0);
	if (!ev)
		return (write(2, "path or eberenmment error\n", 12), 0);
	return(1);
}

int openoutfile(char **av, int ac)
{
	int	outfile;

	outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (outfile == -1)
		return (write(2, "file error\n", 12), exit(1), 0);
	return(outfile);
}

void checkinfile(char**av)
{
	int	infile;

	infile = open(av[1],O_RDWR);
	if (infile == -1)
	{
		perror("pipex");
		exit(1);
	}	
	close(infile);
}

void pipecheck(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
}

void forkfaild(pid_t pid, int*pipefd)
{
	if (pid == -1)
	{
		perror("fork failed");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
}


void loop_childs(int ac, int i, int *pipefd, int *prev_pipe, char **av, char **paths)
{
	pid_t pid;

	while (i < (ac - 2))
	{
		pipecheck(pipefd);
		pid = fork();
		forkfaild(pid, pipefd);
		if (pid == 0)
		{
			if (i == 1)
				first_command(av, paths, pipefd);
			else
				executing(*prev_pipe, av, i, paths, pipefd[1]);
			close(pipefd[0]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(pipefd[1]);
			if (*prev_pipe >= 0)
				close(*prev_pipe);
			*prev_pipe = pipefd[0];
		}
		i++;
	}
}

int	main(int ac, char **av, char **ev)
{
	int pipefd[2];
	char **paths;
	int i;
	int prev_pipe;
	int outfile;

	prev_pipe = -1;
	if (check(ev, ac) == 0)
		return (0);
	outfile = openoutfile(av, ac);
	checkinfile(av);
	paths = takepaths(ev, 0);
	if (!paths)
		return (perror("pipex"), close(outfile), 0);
	loop_childs(ac, 1, pipefd, &prev_pipe, av, paths);
	executing(prev_pipe, av, ac - 2, paths, outfile);
	close(prev_pipe);
	close(outfile);
	wait(NULL);
	return (0);
}
