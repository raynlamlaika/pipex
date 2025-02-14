/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:00:59 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/14 22:50:57 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	search_search(char *next, char *limiter)
{
	char	*full_limiter;
	int		result;

	full_limiter = ft_strjoin(limiter, "\n");
	if (!full_limiter)
		return (exit(1), 1);
	result = ft_strncmp(next, full_limiter, ft_strlen(full_limiter));
	free(full_limiter);
	return (result);
}

void	lines(int fd, char *limiter)
{
	char	*next;

	while (1)
	{
		write(1, "pipex_heredoc >> ", 17);
		next = get_next_line(0);
		if (!next)
			break ;
		if (search_search(next, limiter) == 0)
		{
			free(next);
			break ;
		}
		write(fd, next, ft_strlen(next));
		free(next);
	}
}

int	first_cmd(char **av, char **paths, int *pipfd, int infile)
{
	char	**cmd;
	char	*path;

	if (infile < 0)
		exit(1);
	if (dup2(infile, STDIN_FILENO) == -1)
		return (perror("pipex"), exit(1), 0);
	close(infile);
	if (dup2(pipfd[1], STDOUT_FILENO) == -1)
		return (perror("pipex"), close(pipfd[1]), exit(1), 0);
	close(pipfd[1]);
	close(pipfd[0]);
	cmd = ft_split(av[3], ' ');
	path = pick(paths, cmd[0]);
	if (!path)
		return (perror("pipex"), close(infile), exit(1), 0);
	execve(path, cmd, NULL);
	exit(1);
	return (1);
}

int	last_cmmd(char**av, char**paths, int *pipfd)
{
	int		outfile;
	char	**cmd;
	char	*path;

	outfile = open(av[5], O_CREAT | O_APPEND | O_RDWR, 0644);
	if (outfile == -1)
		return (perror("pipex"), 0);
	if ((dup2(pipfd[0], STDIN_FILENO) == -1))
		return (close(pipfd[0]), close(pipfd[1]), exit(1), 0);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (close(outfile), close(pipfd[1]), exit(1), 0);
	close(pipfd[1]);
	close(outfile);
	cmd = split(av[4]);
	path = pick(paths, cmd[0]);
	if (!path)
		return (perror("pipex"), clean_2(cmd), 0);
	if (execve(path, cmd, NULL) == -1)
		perror("pipex");
	exit(1);
}

int	heredoc(int ac, char **av, char**paths)
{
	char	*limiter;
	int		pipfd[2];
	int		newpip[2];

	if (ac < 6)
		return (perror("pipex"), 1);
	limiter = av[2];
	if (pipe(pipfd) == -1)
		return (perror("pipe"), 1);
	lines(pipfd[1], limiter);
	close(pipfd[1]);
	if (fork() == 0)
	{
		pipecheck(newpip);
		first_cmd(av, paths, newpip, pipfd[0]);
	}
	if (fork() == 0)
		last_cmmd(av, paths, pipfd);
	close(pipfd[0]);
	wait(NULL);
	wait(NULL);
	clean_2(paths);
	return (0);
}
