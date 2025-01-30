#include "pipex.h"

// int	executing(int prev_pipe, char** av, int j, char **paths, int *pipfd)
// {
// 	char	**command;
// 	char	*path;

// 	if(fork() == 0)
// 	{
// 		if ((dup2(prev_pipe, STDIN_FILENO) == -1 )|| \
// 			(dup2(pipfd[1], STDOUT_FILENO) == -1))
// 			return(write(2, "dup2 are failed in this fd\n", 27), 0);
// 		close(pipfd[0]);
// 		command = ft_split(av[j], ' ');
// 		path = pick(paths, av[j]);
// 		execve(path, command, NULL);
// 		exit(0);
// 	}
// 	else
// 		return (0);
// }

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
		command = ft_split(av[j], ' ');
		path = pick(paths, av[j]);
		execve(path, command, NULL);
		exit(1);
	}
	else
		return (0);
}


int main(int ac, char **av, char **ev)
{
    if (ac != 4)
        return (1);

    int infile = open(av[1], O_RDONLY);
    if (infile == -1)
        return (1);

    int outfile = open(av[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile == -1) {
        perror("Error opening outfile");
        close(infile);
        return (1);
    }

    int pifd[2];
    if (pipe(pifd) == -1) {
        perror("Error creating pipe");
        return (1);
    }
    executing(infile, av, 2, takepaths(ev), outfile);
    close(pifd[1]);
    close(infile);
    close(outfile);

    wait(NULL);  // Wait for the child process

    return (0);
}