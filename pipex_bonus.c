/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:13:22 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/29 20:47:42 by rlamlaik         ###   ########.fr       */
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
		cmm = ft_split(av[i], ' ');
		cmd = pick(path, cmm[0]);
		if (!cmd)
		{
			write(2, "cmmand not fond\n",16);
			exit(1);
		}
		i--;
	}
}

int	executing(int prev_pipe, char** av, int j, char **paths, int *pipfd)
{
	char	**command;
	char	*path;

	if(fork() == 0)
	{
		if ((dup2(prev_pipe, STDIN_FILENO) == -1 )|| \
			(dup2(pipfd[1], STDOUT_FILENO) == -1))
			return(write(2, "dup2 are failed in this fd\n", 27), 0);
		close(pipfd[0]);
		command = ft_split(av[j], ' ');
		path = pick(paths, av[j]);
		//exece right here
		execve(path, command, NULL);
		exit(0);
		return(1);
	}
	else
		return (0);
}

int main(int ac, char **av, char **ev)
{
	int		pipefd[2];
	char	**paths;
	int		i;
	int		prev_pipe;

	if (pipe(pipefd) == -1)
		return (write(2, "pipe filed\n", 12), 0);
	if (ac < 5) //need to modifie
		return(write(2, "args not enogh\n", 16), 0);
	paths = takepaths(ev);
	//check_command(ac, av, paths); faut
	if (!paths)
		return(write(2, "path error\n", 12), 0);
	// pass the command unitily get the  file 2
	i = ac - 3;
	int j = 3;
	if (fork() == 0)
		first_command(av, paths, pipefd);
	prev_pipe = pipefd[0];
	close(pipefd[1]);
	while(j - 1 != i)
	{
		if (pipe(pipefd) == -1)
			return (write(2, "pipe filed\n", 12), 0);
		executing(prev_pipe, av, j, paths, pipefd);
		close(pipefd[1]);
		prev_pipe = pipefd[0];
		j++;
	}
	close(pipefd[1]);
	if (fork() == 0)
		last_commmand(ac, av, ev, paths, pipefd);
	close(pipefd[0]);
	wait(NULL);
	return (0);
}
