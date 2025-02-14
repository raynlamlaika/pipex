/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:00:59 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/14 19:55:58 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	search_search(char *next, char *limiter)
{
	char	*full_limiter;
	int		result;

	full_limiter = ft_strjoin(limiter, "\n");
	if (!full_limiter)
		return (exit(1), 1);
	result = ft_strncmp(next, full_limiter, ft_strlen(full_limiter));
	free(full_limiter);
	return (result);
}

void lines(int fd, char *limiter)
{
	char	*next;

	while (1)
	{
		write(1, "pipex_heredoc >> ", 17);
		next = get_next_line(0);
		if (!next)
			break ;
		if (search_search(next, limiter) == 0)
		{
			free(next);
			break ;
		}
		write(fd, next, ft_strlen(next));
		free(next);
	}
}

int heredoc(int ac, char **av)
{
	char *limiter;
	int pipfd[2];

	if (ac < 6)
	{
		fprintf(stderr,"Usage: ./pipex here_doc LIMITER cmd1 cmd2 file\n");
		return (1);
	}
	limiter = av[2];
	if (pipe(pipfd) == -1)
	{
		perror("pipe");
		return (1);
	}
	lines(pipfd[1], limiter);
	close(pipfd[1]);

	char *gg =get_next_line(pipfd[0]);
	printf("this is the thing %s\n", gg);
	// the pipefd hold the  data pip[1] that we can read it and pass it 
	//exectute the command into the pip[] First one

	//second one



	return (0);
}
