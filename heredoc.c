/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 20:00:59 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/08 20:14:47 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

char	**moooves(int i, char *er)
{
	char	**moves;
	char	*tmpp;
	char	*next;
	char	*oprt;

	oprt = ft_strdup("");
	if (!oprt)
		return (free(oprt), NULL);
	next = get_next_line(0);
	while (next)
	{
		i = search_search(next);
		tmpp = oprt;
		oprt = ft_strjoin(oprt, next);
		if (!oprt || i == 0)
			return (free(oprt), free(next), free(tmpp), NULL);
		free(tmpp);
		free(next);
		next = get_next_line(0);
	}
	moves = ft_split(oprt, '\n');
	return (free(oprt), free(next), moves);
}
int	heredoc(int ac, char**av, char**ev)
{
	char*	limiter;

	//take the commends
	

	return (0);
}

