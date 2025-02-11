/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 22:51:37 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/11 09:42:22 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
