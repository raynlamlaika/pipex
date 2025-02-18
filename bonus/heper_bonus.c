/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heper_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:03:11 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/18 11:16:29 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipexb.h"

void	pipecheck(int *pipefd)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

void	forkfaild(pid_t pid, int*pipefd)
{
	if (pid == -1)
	{
		perror("pipex");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
}

void	handelprevpipe(int *pipefd, int *prev_pipe)
{
	close(pipefd[1]);
	close(*prev_pipe);
	*prev_pipe = pipefd[0];
}

int	last_child(int prvpipe, char*cmd, char**paths, int outf)
{
	char	**command;
	char	*path;

	if (fork() == 0)
	{
		if (dup2(prvpipe, STDIN_FILENO) == -1)
			return (perror("pipex"), 0);
		close(prvpipe);
		if (dup2(outf, STDOUT_FILENO) == -1)
			return (perror("pipex"), close(prvpipe), 0);
		close(outf);
		command = split(cmd);
		if (!command)
			return (clean_2(command), 0);
		path = pick(paths, command[0]);
		if (!path)
			return (perror("pipex"), close(prvpipe), close(outf), exit(1), 0);
		if (execve(path, command, NULL) == -1)
		{
			perror("pipex");
			exit(1);
		}
	}
	return (0);
}

void	loop_childs(int ac, int *prev_pipe, char **av, char **paths)
{
	pid_t	pid;
	int		i;
	int		pipefd[2];

	i = 1;
	while (i < (ac - 3))
	{
		pipecheck(pipefd);
		pid = fork();
		forkfaild(pid, pipefd);
		if (pid == 0)
		{
			if (i == 1)
				first_command(av, paths, pipefd);
			if (i > 1)
			{
				close(pipefd[0]);
				executing(*prev_pipe, av[i + 1], paths, pipefd[1]);
			}
		}
		else
			handelprevpipe(pipefd, prev_pipe);
		i++;
	}
}
