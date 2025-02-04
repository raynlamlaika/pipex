/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 09:26:45 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/04 17:29:47 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	nbr_words(char*string)
{
	int	numberofwords;
	int	helper;

	numberofwords = 0;
	helper = 0;
	while (*string)
	{
		if ((*string != '\'' && *string != ' ') && helper == 0)
		{
			numberofwords++;
			helper = 1;
		}
		else if (*string == '\'' || *string == ' ')
			helper = 0;
		string++;
	}
	return (numberofwords);
}

static int	lenghtofword(char*string)
{
	int	i;

	i = 0;
	while (*string && (*string != ' ' && *string != '\''))
	{
		i++;
		string++;
	}
	return (i);
}

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	**toothe_array(char *str, char **resulte, int *index)
{
	unsigned int	words;

	while (*str)
	{
		while (*str == ' ' || *str == '\'')
			str++;
		if (*str != ' ' && *str != '\'' && *str != '\0')
		{
			words = lenghtofword(str);
			resulte[*index] = (char *) malloc((words + 1) * sizeof(char));
			if (!resulte[*index])
			{
				while (*index > 0)
					free(resulte[--(*index)]);
				free(resulte);
				return (NULL);
			}
			ft_strncpy(resulte[*index], str, words);
			resulte[*index][words] = '\0';
			(*index)++;
			str += words;
		}
	}
	return (resulte);
}

char	**split(char *str)
{
	char	**resulte;
	int		words;
	int		index;

	words = nbr_words(str);
	resulte = (char **) malloc(sizeof(char *) * (words + 1));
	if (!resulte)
		return (NULL);
	index = 0;
	if (!toothe_array(str, resulte, &index))
		return (NULL);
	resulte[index] = NULL;
	return (resulte);
}
