/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 15:52:47 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/21 18:44:41 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**takepath(char** env)
{
	char	*pathstr;
	char	**back;
	int		enc;

	enc = 0;
	pathstr = env[76] + 5;
	back = ft_split(pathstr, ':');
	while (back[enc])
	{
		back[enc] = ft_strjoin(back[enc] , "/");
		enc++;
	}
	return(back);
}

char	*pick(char **path,int ac, char ** av)
{
	int		pass;
	char	*realpath;

	pass = 0;
	while (path[pass])
	{
		realpath = ft_strjoin(path[pass], av[3]);
		if (access(realpath, X_OK) == 0)
			return(realpath);
		pass++;
	}
	return (NULL);
}

int main(int ac , char **av, char **ev)
{
	int		pipefd[2];
	int		pid;
	char	**path;
	char	*lavraipath;

	
	if (ac == 5)
	{
		pid = fork();
		if (pipe(pipefd) == -1)
			return(write(2, "Foooork makhadamach\n", 21), 0);
		if(pid == 0)
		{
			path = takepath(ev);
			lavraipath = pick(path, ac, av);
			printf("c\'est la vrai path :%s\n", lavraipath);
		}

		exit(EXIT_SUCCESS);
	}
    return (0);
}