/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:13:22 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/07 20:25:41 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	executing(int prev_pipe, char*cmd, char**paths, int outfile)
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
		command = split(cmd);
		if (!command)
			return (clean_2(command), 0);
		path = pick(paths, command[0]);
		if (!path)
			return ;
		if (execve(path, command, NULL) == -1)
		{
			perror("pipex");
			exit(1);
		}
	}
	return (0);
}

int	check(int ac)
{
	if (ac < 5)
		return (perror("pipex"), 0);
	return (1);
}

int	openoutfile(char **av, int ac)
{
	int	outfile;

	outfile = open(av[ac - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (outfile == -1)
		return (perror("pipex"), exit(1), 0);
	return (outfile);
}

void	checkinfile(char**av)
{
	int	infile;

	infile = open(av[1], O_RDWR);
	if (infile == -1)
	{
		perror("pipex");
		exit(1);
	}
	close(infile);
}

int	main(int ac, char **av, char **ev)
{
	char	**paths;
	int		prev_pipe;
	int		outfile;

	prev_pipe = -1;
	if (check(ac) == 0)
		return (0);
	outfile = openoutfile(av, ac);
	checkinfile(av);
	paths = takepaths(ev, 0);
	// if (!paths)
	// 	return (perror("pipex"), close(outfile), 0);
	// fprintf(stderr, "thi aia is for the debug habibi\n");
	loop_childs(ac, &prev_pipe, av, paths);
	executing(prev_pipe, av[ac - 2], paths, outfile);
	close(prev_pipe);
	close(outfile);
	wait(NULL);
	return (0);
}
