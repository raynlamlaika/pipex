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
	if (access("/bin/cat", X_OK) == 0)
		return (write(1, "ra 9raa 9ra \n", 14), 0);
	else
		return (write(1, "khadamach", 10), 0);

thisis s



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