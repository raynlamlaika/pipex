/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:51:37 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/08 20:09:12 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char*source)
{
	size_t	o;
	char	*sp;

	o = 0;
	sp = (char *) malloc((ft_strlen(source)+ 1) * sizeof(char));
	if (!sp)
		return (NULL);
	while (source[o])
	{
		sp[o] = source[o];
		o++;
	}
	sp[o] = '\0';
	return (sp);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*ptr;
	char	x;

	if (!str)
		return (NULL);
	ptr = (char *)str;
	x = (char)c;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == x)
			return ((char *)(ptr + i));
		i++;
	}
	if (x == '\0')
		return ((char *)(ptr + i));
	return (NULL);
}

char	*checkgnl(char const *s1, char const *s2)
{
	char	*p;

	if (!s1)
	{
		p = ft_strdup(s2);
		return (p);
	}
	if (!s2)
	{
		p = ft_strdup(s1);
		return (p);
	}
	else
		return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*ptr;

	if (!s1 && !s2)
		return (0);
	if ((!s1 && s2) || (!s2 && s1))
		return (checkgnl(s1, s2));
	i = ft_strlen(s1)+ ft_strlen(s2);
	ptr = (char *) malloc((i + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		ptr[i] = *s2;
		i++;
		s2++;
	}
	ptr[i] = '\0';
	return (ptr);
}
