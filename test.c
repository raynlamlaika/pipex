#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include "pipex.h"

// char **searsh_path(char **ev)
// {
// 	char  **thepath;
// 	int   i;

// 	i = 0;
// 	char *ii = ev[76] + 5;
// 	printf("%s\n", ii);
// 	thepath = ft_split(ii, ':');
// 	return (thepath);
// }

// int main(int ac, char **av, char **ev)
// {
// 	int i;
// 	int pipefd[2];
// 	int pid;

// 	char *cat[]={"/bin/cat", "file1", NULL};
// 	pipe(pipefd);

// 	if (pid == 0)
// 	{



// 	}


	// if (ac == 5)
	// {
	// 	i = open(av[1], O_RDONLY, 0777);
	// 	if (i < 0)
	// 		return (write(2 ,"mochkil f file1", 16), 0);
	// 	if (fork() == 0)
	// 	{
	// 		if (execve(NULL,NULL, NULL)== -1)
	// 			return (write(1, "execve failed", 14), 0);



	// 	}

// 	}
// }



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int ac, char **av, char **ev)
{


// first work with access to check if the path are exec
//	it return -1 if it failed and 0 for success
// the first arg is the path to access or test and
//			secd one is R_OK W_OK ...
//	R_OK
//		Test for read permission.

// 	W_OK
//		 Test for write permission.

// 	X_OK
// 		Test for execute or search permission.

//	 F_OK
// 		Check existence of file

//prototype int access(const char *pathname, int mode);
	printf("\t----- to the access function -----\n");

	if (access("/bin/cat", X_OK) == 0)
		write(1, "ra 9ra\n", 8);
	else
		return (write(1, "khadamach", 10), 0);
	if (access("/home/rlamlaik/Desktop/pipex", F_OK) == 0)
		write(1, "acces passed \n", 15);
	else
		return (write(1, "khadamach", 10), 0);

// 2eme function  is Dup2() &dup()
	int copy;
	int i = open ("file1",O_RDWR , 0777);
	printf("\t----- to the dup & dup2 function -----\n");

	if (i < 0)
		write(2, "pblem f open \n", 15);
	else
	{
		copy = dup(i);
		printf("the return val of open :%d\nreturn val of dup:%d\n", i, copy);
		write(copy, "HADCHI FIN AYTAKTAB\n", 21);
		write(i, "the same one or waht ", 21);
		write(copy, "HADCHI FIN AYTAKTAB\n", 21);
		write(copy, "HADCHI FIN AYTAKTAB\n", 21);
		write(i, "the same one or waht ", 21);
		write(i, "the same one or waht ", 21);
		//even the copy are deffrent then value of i but 
		// both of them refure to the file 

		//dup2()
		// do the same thing but with one additional thing that
		// u can add in integer to sepicifie the fd
		close(copy);
		i = dup2(copy, 1);
		printf("this is return val of dup2 in fail case (close fd)%d\n", i);
		printf("\n thisis will be writing in stdout or waht !!\n");
		// the output of print if it will be in the file cuz we use dup 2
		// the it add the fb of copy for all all of them refure to the same file 
		write(copy,"alo\n",4);
	}
	
	
	printf("\n\t----- to the pipe function -----\n");
	// first the prototype of the pipe is int pipe(int pipefd[2]);
	
	
	
	
	
	int fd[2];
	if (pipe(fd) == -1)
		return (write(1,"the pipe is faillld \n", 22), 0);
	pid_t pid = fork();
	if (pid== 0)
	{
		// the fork it will be retuen 0 if that it creat | or if th we re in child child proccese
		// so rn if fork isn't fialed we are in child proccess
		write(fd[1], "kifach\n", 8);
		printf("this is the val of fd[1] :%d\nand the fd[0]:%d\n", fd[1], fd[0]);
		//printf("hada child process\n");
	}
	else 
		printf("4ALAAT\n");
	//printf("hada w ------ewew \n");
	// waitpid(pid, NULL, 0);
	char buff[8];
	read(fd[0], buff, 8);
	printf("thsiis the buffer the we pipe from the child :%s\n", buff);
	// it writing it twice cuz of the fork the we do creat in tow proccess
	//exit(0);


	printf("\n\t----- to the fork function -----\n\n\n");
	// no need right now it just creat in child prcess that i will pic more in the the draw

	printf("\n\t----- to the execve function -----\n");
	// is in function to aplic the bash script one big thing that u may need to know
	// is that execve it replace the full procces with the thing that he need to execute

	// the prototypee int execve(path to the command, that inpuut for the command , the everonment);
	//



// 	char *const envp[]:

// This is the environment vector, an array of strings representing the environment variables for the new program.
// Each string in the array should be of the form KEY=VALUE, e.g., "PATH=/usr/bin".
// Pass NULL if you want the new program to inherit the parent process's environment.
	char * const yy[] = {"/usr/bin/echo", "HELLLO\n", NULL};
	printf("-p-p-p-p-p-\n");
	execve("/usr/bin/echo", yy, NULL);
	printf ("wvw\n");


}


/*
1. Vérifier les arguments d'entrée
	- Si le nombre d'arguments est incorrect, afficher une erreur et quitter.

2. Ouvrir file1 en lecture
	- Si l'ouverture échoue, afficher une erreur et quitter.

3. Ouvrir file2 en écriture (créer ou tronquer)
	- Si l'ouverture échoue, afficher une erreur et quitter.

4. Créer un pipe
	- Si la création échoue, afficher une erreur et quitter.

5. Fork pour le premier processus (cmd1)
	- Dans le processus enfant :
		 - Rediriger l'entrée vers file1.
		 - Rediriger la sortie vers l'extrémité d'écriture du pipe.
		 - Fermer les extrémités inutilisées du pipe.
		 - Exécuter cmd1 avec execve.
	- Dans le processus parent :
		 - Fermer l'extrémité d'écriture du pipe.

6. Fork pour le second processus (cmd2)
	- Dans le processus enfant :
		 - Rediriger l'entrée vers l'extrémité de lecture du pipe.
		 - Rediriger la sortie vers file2.
		 - Fermer les extrémités inutilisées du pipe.
		 - Exécuter cmd2 avec execve.
	- Dans le processus parent :
		 - Fermer l'extrémité de lecture du pipe.

7. Attendre que les processus enfants se terminent.

8. Fermer les fichiers ouverts.

9. Quitter le programme.
*/















/*
#include "pipex.h"

char **takepath(char **env)
{
    char *pathstr;
    char **back;
    int enc = 0;

    while (env[enc])
    {
        if (strncmp("PATH=", env[enc], 5) == 0)
            break;
        enc++;
    }

    if (!env[enc]) // PATH not found
        return (NULL);

    pathstr = env[enc] + 5;
    back = ft_split(pathstr, ':');
    for (int i = 0; back[i]; i++)
    {
        char *temp = back[i];
        back[i] = ft_strjoin(back[i], "/");
        free(temp);
    }
    return (back);
}

char *pick(char **path, char *cmd)
{
    int pass = 0;
    char *realpath;

    while (path[pass])
    {
        realpath = ft_strjoin(path[pass], cmd);
        if (access(realpath, X_OK) == 0)
            return (realpath);
        free(realpath);
        pass++;
    }
    return (NULL);
}

int main(int ac, char **av, char **ev)
{
    int pipefd[2];
    pid_t pid;
    char **path;
    char *lavraipath;
    int infile, outfile;

    if (ac == 5)
    {
        infile = open(av[1], O_RDONLY);
        if (infile < 0)
            return (perror("Error opening infile"), 1);

        outfile = open(av[4], O_RDWR | O_CREAT | O_APPEND, 0644);
        if (outfile < 0)
            return (perror("Error opening outfile"), 1);

        if (pipe(pipefd) == -1)
            return (perror("Pipe failed"), 1);

        path = takepath(ev);
        if (!path)
            return (write(2, "PATH not found\n", 15), 1);

        pid = fork();
        if (pid < 0)
            return (perror("Fork failed"), 1);

        if (pid == 0) // Child process
        {
            close(pipefd[0]);
            dup2(infile, STDIN_FILENO);
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);
            close(infile);

            lavraipath = pick(path, av[2]);
            if (!lavraipath)
                return (write(2, "Command not found\n", 18), 1);

            char *const mesage[] = {av[2], NULL};
            execve(lavraipath, mesage, ev);
            perror("Execve failed");
            exit(1);
        }
        else // Parent process
        {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            dup2(outfile, STDOUT_FILENO);
            close(pipefd[0]);
            close(outfile);

            lavraipath = pick(path, av[3]);
            if (!lavraipath)
                return (write(2, "Command not found for parent\n", 29), 1);

            char *const fff[] = {av[3], NULL};
            execve(lavraipath, fff, ev);
            perror("Execve failed");
            exit(1);
        }
    }
    return (0);
}


*/