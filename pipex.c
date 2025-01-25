/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:49:31 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/25 19:25:17 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**takepaths(char** env)
{
	char	*pathstr;
	char	**back;
	int		enc;

	if (!env)
		exit(EXIT_FAILURE);
	enc = 0;
	int i = 0;
	while (env[enc])
	{
		if (ft_strncmp("PATH=", env[enc], 5) == 0)
			break ;
		enc++;
	}
	if (!env[enc])
		return (NULL);
	pathstr = env[enc] + 5;
	enc = 0;
	back = ft_split(pathstr, ':');
	while (back[enc])
	{
		back[enc] = ft_strjoin(back[enc] , "/");
		enc++;
	}
	return(back);
}

char	*pick(char **path,char* cmd)
{
	int		pass;
	char	*realpath;

	pass = 0;

	while (path[pass])
	{
		
		realpath = ft_strjoin(path[pass], cmd);
		if (access(realpath, X_OK) == 0)
			return(realpath);
		free(realpath);
		pass++;
	}
	return (NULL);
}

void	firstcmd(char **av, char **paths, int *pipfd)
{
	char	**cmd;
	char	*path;
	int		infile;

	infile = open(av[1], O_RDONLY);
	if (infile < 0)
		return ;
	if (dup2(infile, STDIN_FILENO) == -1 || dup2(pipfd[1], STDOUT_FILENO) == -1)
		return ;
	cmd = ft_split(av[2], ' ');
	path = pick(paths, cmd[0]);
	close(infile);
	if (!path)
		return ;
	execve(path, cmd, NULL);
	return ;
}

int main (int ac, char **av, char **ev)
{
	int		pipfd[2];
	pid_t	pid;
	char	**paths;
	char	*path;
	int		outfile;

	if (ac != 5)
		exit(EXIT_FAILURE);
	if (pipe(pipfd) == -1)
		return (0);
	paths = takepaths(ev);
	pid = fork();
	if (pid == -1)
		return (write(2, "fork failed\n", 13), 0);
	if(pid == 0)
		firstcmd(av, paths, pipfd);
	else 
	{
		outfile = open(av[4], O_APPEND | O_CREAT | O_RDWR, 0644);
		if (outfile == -1)
			return (write(1, "open failed 1\n", 15), 0);
		if (dup2(pipfd[0], STDIN_FILENO) == -1 ||dup2(outfile, STDOUT_FILENO) == -1)
			return (0);
		close(pipfd[1]);
		char **cmd= ft_split(av[3], ' ');
		path = pick(paths, cmd[0]);
		if (!path)
			return (write(1, "wewe\n", 5), 0);
		wait(NULL);
		execve(path, cmd, ev);
	}
	return (0);
}

