/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 13:13:22 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/02 16:28:47 by rlamlaik         ###   ########.fr       */
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
		cmm = split(av[i]);
		cmd = pick(path, cmm[0]);
		if (!cmd)
		{
			write(2, "cmmand not fond\n",16);
			exit(1);
		}
		i--;
	}
}

int	executing(int prev_pipe, char** av, int j, char **paths, int outfile)
{
	char	**command;
	char	*path;

	if(fork() == 0)
	{
		if ((dup2(prev_pipe, STDIN_FILENO) == -1) || \
			(dup2(outfile, STDOUT_FILENO) == -1))
			return (write(2, "dup2 failed\n", 12), 0);
		close(outfile);
		command = split(av[j]);
		path = pick(paths, av[j]);
		execve(path, command, NULL);
		exit(1);
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
	if (ac < 5)
		return(write(2, "args not enogh\n", 16), 0);
	paths = takepaths(ev);
	if (!paths)
		return(write(2, "path error\n", 12), 0);
	int infile = open(av[1], O_RDONLY);
	int outfile = open(av[(ac - 1)], O_CREAT | O_TRUNC | O_APPEND | O_RDWR, 0644);
	if (infile == -1 || outfile == -1)
		return (write(2, "no infile/outfile of waht \n", 27), 0);
	i = 1;
    while (i < ac - 2)
    {
		if (i == 1)
			if (fork() == 0)
			{
				first_command(av, paths, pipefd);
				prev_pipe = pipefd[0];
			}
		else 
		{
			if (pipe(pipefd) == -1)
				return (write(2, "pipe failed\n", 12), 0);
			executing(prev_pipe, av, i, paths, pipefd[1]);
			fprintf(stderr, "thisis the av file || cnmd [%s] and [%d] \n", av[i], i);
		}
		i++;
	}
    executing(prev_pipe, av, i, paths, outfile);
    close(prev_pipe);
    close(outfile);
    wait(NULL);
    return (0);
}


//finish pipex 
// int executing(int prev_pipe, char **av, int j, char **paths, int outfile)
// {
//     char **command;
//     char *path;

//     if (fork() == 0)
//     {
//         if (dup2(prev_pipe, STDIN_FILENO) == -1 || \
//             dup2(outfile, STDOUT_FILENO) == -1)
//             return (write(2, "dup2 failed\n", 12), 0);

//         close(prev_pipe);
//         close(outfile);

//         command = ft_split(av[j], ' ');
//         path = pick(paths, av[j]);
//         execve(path, command, NULL);
//         exit(1); // If execve fails
//     }
//     else
//         return (0);
// }

// int main(int ac, char **av, char **ev)
// {
//     int pipefd[2];
//     char **paths;
//     int i;
//     int prev_pipe;

//     if (pipe(pipefd) == -1)
//         return (write(2, "pipe failed\n", 13), 0);
//     if (ac < 5)
//         return (write(2, "args not enough\n", 17), 0);

//     paths = takepaths(ev);
//     if (!paths)
//         return (write(2, "path error\n", 12), 0);

//     int outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (outfile == -1)
//     {
//         perror("Error opening outfile");
//         return (1);
//     }

//     i = 2; // Commands start from av[2]
//     prev_pipe = pipefd[0];

//     while (i < ac - 2)
//     {
//         if (pipe(pipefd) == -1)
//             return (write(2, "pipe failed\n", 13), 0);

//         executing(prev_pipe, av, i, paths, pipefd[1]);

//         close(pipefd[1]);
//         close(prev_pipe);
//         prev_pipe = pipefd[0];
//         i++;
//     }

//     executing(prev_pipe, av, i, paths, outfile);

//     close(prev_pipe);
//     close(outfile);

//     wait(NULL); // Wait for child processes

//     return (0);
// }