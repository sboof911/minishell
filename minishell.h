/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:21:13 by amaach            #+#    #+#             */
/*   Updated: 2021/07/08 13:51:05 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define EXPANSION -36
# define ERROR 1
# define SUCCESS 0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

char	**protection_malloc2(char **str, int compt);
char	*protection_malloc1(char *str, int compt);
void	*ft_free(char **s, int i);
char	**ft_split(char const *s, char c);
char	**split_pipe(char const *s, char c);
char	*ft_strdup(const char *s);
int		ft_strlen(char *str);
int		ft_isalpha(int c);
void	ft_putstr(char *s);
void	ft_putchar(char c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_putnbr(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		is_builtin(char *command);
int		ft_pwd(void);
int     exec_builtin(char **cmd);

#endif