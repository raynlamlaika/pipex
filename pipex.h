/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:38:23 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/01/26 16:03:28 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#  define PIPEX_H


#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/wait.h>
 
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int     ft_strncmp(const char *str1, const char *str2, size_t num);
char	*ft_strrchr(const char *str, int c);
size_t	ft_strlen(const char *str);
char	**takepaths(char **env);
char	*pick(char**path, char*cmd);

#endif
