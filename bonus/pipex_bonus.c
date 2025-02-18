/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:13:22 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/18 11:16:36 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipexb.h"

int	executing(int prev_pipe, char*cmd, char**paths, int outfile)
{
	char	**command;
	char	*path;

	if (dup2(prev_pipe, STDIN_FILENO) == -1)
		return (perror("pipex"), 0);
	close(prev_pipe);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		return (perror("pipex"), close(prev_pipe), 0);
	close(outfile);
	command = split(cmd);
	if (!command)
		return (clean_2(command), 0);
	path = pick(paths, command[0]);
	if (!path)
		return (perror("pipex"), close(prev_pipe), close(outfile), exit(1), 0);
	if (execve(path, command, NULL) == -1)
	{
		perror("pipex");
		exit(1);
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
	paths = takepaths(ev, 0);
	if (ft_strncmp("here_doc", av[1], 9) == 0)
		return (heredoc(ac, av, paths), 0);
	outfile = openoutfile(av, ac);
	checkinfile(av);
	loop_childs(ac, &prev_pipe, av, paths);
	last_child(prev_pipe, av[ac - 2], paths, outfile);
	close(prev_pipe);
	close(outfile);
	clean_2(paths);
	while (wait(NULL) != -1)
		;
	return (0);
}
