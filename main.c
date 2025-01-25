/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:52:47 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/25 14:19:44 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**takepath(char** env)
{
	char	*pathstr;
	char	**back;
	int		enc;

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

char **cmdparce(char **av)
{
	char **take;

	take = ft_split(av[2], ' ');
	return (take);
}

int main(int ac , char **av, char **ev)
{
	int			pipefd[2];
	int			pid;
	char		**path;
	char		*lavraipath;
	int			infile;
	int			outfile;
	char* const	*command;

	if (ac == 5)
	{
		infile = open(av[1], O_RDONLY);
		outfile = open(av[4], O_RDWR | O_CREAT | O_APPEND);
		if (infile < 0 || outfile < 0)
			return (perror("Error opening file"), 1);
		if (pipe(pipefd) == -1)
			return(write(2, "Piipeee makhadamach\n", 21), 0);
		pid = fork();
		path = takepath(ev);
		if(pid == 0)
		{
			// close(pipefd[0]);
			dup2(infile, STDIN_FILENO);
			dup2(pipefd[1], STDOUT_FILENO);
			command = cmdparce(av);
			lavraipath = pick(path, command[0]);
			close(infile);
			if(!lavraipath)
				return (write(2, "lavrai path makinach1\n", 23), 0);
			if (!lavraipath)
				return (write(1, "lavraie pathd zape\n", 20), 0);
			execve(lavraipath, command, NULL);
		}
		else
		{
			close(pipefd[1]);
			close(infile);
			dup2(pipefd[0], STDIN_FILENO);
			dup2(outfile, STDOUT_FILENO);
			lavraipath = pick(path, av[3]);
			if(!lavraipath)
				return (write(2, "lavrai path makinach2\n", 23), 0);
			char *const fff[] = {av[3], NULL};
			wait(NULL);
			execve(lavraipath, fff, ev);
			perror("Execve failed");
		}
	}
	return (0);
}