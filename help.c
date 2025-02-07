/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:02:54 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/07 14:48:30 by rlamlaik         ###   ########.fr       */
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

char	**takepaths(char **env, int enc)
{
	char	*pathstr;
	char	**back;
	char	*helper;

	if (!env)
		return (NULL);
	while (env[enc])
	{
		if (ft_strncmp("PATH=", env[enc], 5) == 0)
			break ;
		enc++;
	}
	if (!env[enc])
		return (NULL);
	pathstr = env[enc] + 5;
	back = ft_split(pathstr, ':');
	enc = 0;
	while (back[enc])
	{
		helper = back[enc];
		back[enc] = ft_strjoin(back[enc], "/");
		free(helper);
		enc++;
	}
	return (back);
}

char	*pick(char**path, char*cmd)
{
	int		pass;
	char	*realpath;
	char	**cmdpath;

	pass = 0;
	if (ft_strrchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			cmdpath = ft_split(cmd, ' ');
			return (cmdpath[0]);
		}
		return (NULL);
	}
	if (!path)
		return (perror("pipex"), exit(1), NULL);
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

void	clean_2(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		ptr[i] = NULL;
		i++;
	}
	free(ptr);
	ptr = NULL;
}
