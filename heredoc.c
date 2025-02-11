/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:00:59 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/11 10:10:19 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	search_search(char *next, char *limiter)
{
	limiter = ft_strjoin(limiter, "\n");
	if (ft_strncmp(next, limiter, ft_strlen(limiter)) == 0)
	{
		printf("sf saliina");
		exit(0);
	}
	return (1);
}

char	**moooves(int i, char *limiter)
{
	char	**moves;
	char	*tmpp;
	char	*next;
	char	*oprt;

	oprt = ft_strdup("");
	if (!oprt)
		return (free(oprt), NULL);
	write(1, "pipex_herdoc> ", 14);
	next = get_next_line(0);
	while (next)
	{
		i = search_search(next, limiter);
		tmpp = oprt;
		oprt = ft_strjoin(oprt, next);
		if (!oprt || i == 0)
			return (free(oprt), free(next), free(tmpp), exit(1), NULL);
		free(tmpp);
		free(next);
		write(1, "pipex_herdoc >", 14);
		next = get_next_line(0);
	}
	moves = ft_split(oprt, '\n');
	return (free(oprt), free(next), moves);
}

void	heredoc(int ac, char**av)
{
	char	*limiter;

	limiter = av[2];
	ac = 0;
	printf("so this is the limiter %s\n", limiter);
	moooves(0, limiter);
	exit(0);
	return ;
}
