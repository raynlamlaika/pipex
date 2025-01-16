/*
   ----Pipex----


	-First let's start with run in multiple processes
	with using fork, dup and maybe pipe.
(-ps -ef --forest) withis command we can see all prcesses runing on your pc
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
// First take the parametaer 'file first and the last'
//applay the first command on the file 1 
//copy the output into other file with dump2()
//pass the output of the first command to the second command 
//push the output of that to the last file in argemmnet

int main(int ac, char **av)//, char **ev)
{
	int	i;
	int	j;

	i = 1;
	char *file1;
	char *file2;
	char *txt;


	if (ac == 5)
	{
		file1 = av[1];
		file2 = av[ac - 1];
		j = open(file1, O_RDWR, 0777);
		if (j == -1)
			return (write(1, "prblm in open", 14), 0);
		read(j,txt,4);
		write(1, txt,4);

		//everthing are between those files are command "mindatory only 2 command"

		
	}
}
