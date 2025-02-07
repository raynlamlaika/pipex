/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_heper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:03:11 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/06 15:22:42 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	loop_childs(int ac, int *prev_pipe, char **av, char **paths)
{
	pid_t	pid;
	int		i;
	int		pipefd[2];

	i = 1;
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
				executing(*prev_pipe, av[i], paths, pipefd[1]);
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
