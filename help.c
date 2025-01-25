/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:02:54 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/25 19:16:42 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

char	*ft_strrchr(const char *str, int c)
{
	size_t	i;
	char	*ptr;
	char	a;

	a = (char)c;
	ptr = (char *)str;
	i = ft_strlen(str);
	while (i > 0 && ptr[i] != a)
	{
		i--;
	}
	if (ptr[i] == a)
		return ((char *)&ptr[i]);
	else
		return (NULL);
}
