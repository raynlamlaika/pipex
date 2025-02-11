/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:41:36 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/11 05:17:11 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_command(char **av, char **paths, int *pipfd)
{
	char	**cmd;
	char	*path;
	int		infile;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		exit(1);
	if (dup2(infile, STDIN_FILENO) == -1)
		return (perror("pipex"), exit(1), 0);
	close(infile);
	close(pipfd[0]);
	if (dup2(pipfd[1], STDOUT_FILENO) == -1)
		return (perror("pipex"), close(pipfd[1]),  exit(1), 0);
	close(pipfd[1]);
	cmd = ft_split(av[2], ' ');
	path = pick(paths, cmd[0]);
	fprintf(stderr, "thissis the cmd : |%s| \nthe pipfd[1] : [%d] \npipifd[0]: [%d] \nthe path: |%s|\n", cmd[0], pipfd[1], pipfd[0], path);
	if (!path)
		return (perror("pipex"),close(infile), exit(1), 0);
	execve(path, cmd, NULL);
	exit(1);
	return (1);
}
