/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:13:22 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/11 05:15:04 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	fprintf(stderr, "\n\nthissis the cmd : |%s| \nthe output: [%d] \nprev_pipe: [%d] \nthe path: |%s|\n", cmd, outfile, prev_pipe, path);
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
	// close(outfile);
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

	// if (ft_strcmp("here_doc", av[1], 9) == 0)
	// 	heredoc(ac, av, ev);
	prev_pipe = -1;
	if (check(ac) == 0)
		return (0);
	outfile = openoutfile(av, ac);
	checkinfile(av);
	paths = takepaths(ev, 0);
	// close(0);
	loop_childs(ac, &prev_pipe, av, paths);
	last_child(prev_pipe, av[ac - 2], paths, outfile);
	close(prev_pipe);
	close(outfile);
	// close(0);
	while(waitpid(-1, NULL, 0) != -1)
		;
	return (0);
}
