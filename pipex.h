/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:38:23 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/02/08 13:37:40 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/wait.h>

char	**ft_split(char const*s, char c);
char	*ft_strjoin(char const*s1, char const*s2);
int		ft_strncmp(const char*str1, const char*str2, size_t num);
char	*ft_strrchr(const char*str, int c);
size_t	ft_strlen(const char *str);
char	**takepaths(char**env, int enc);
char	*pick(char**path, char*cmd);
int    	first_command(char **av, char**paths, int *pipfd);
char	**split(char*str);
void	clean_2(char**ptr);
void	pipecheck(int *pipefd);
void	forkfaild(pid_t pid, int*pipefd);
void	loop_childs(int ac, int *prev_pipe, char **av, char **paths);
int		executing(int prev_pipe, char*cmd, char**paths, int outfile);
// void	closingchild(int*pipefd, int *prev_pipe);

#endif
