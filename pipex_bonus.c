/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:13:22 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/28 17:44:44 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_cmd(int ac, char **av, char**path)
{
	int		i;
	char	*cmd;

	i = ac - 2;
	while (i - 1)
	{
		printf("%d\n", i);
		cmd = pick(path, av[i]);
		if (!cmd)
		{
			write(2, "cmmand not fond\n",16);
			exit(1);
		}
		i--;
	}
}

void	executing(int ac,char** av, int j, char **path)
{




}

int main(int ac, char **av, char **ev)
{
	int		infile;
	int		pipefd[2];
	char	**path;
	int	i;

	if (pipe(pipefd) == -1)
		return (write(2, "pipe filed\n", 12), 0);
	if (ac <= 1) //need to modifie
		return(write(2, "args not enogh\n", 16), 0);
	path = takepaths(ev);
	if (!path)
		return(write(2, "path error\n", 12), 0);
	check_cmd(ac, av, path);
	// pass the command unitily get the  file 2
	i = ac - 2;
	int j = 1;
	while(j - 1 != i)
	{
		executing(ac, av, j,path);
		j++;
	}
	infile = open(av[2], O_RDWR );
	i = 0;
	
	return (0);
}
