/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:21:13 by amaach            #+#    #+#             */
/*   Updated: 2021/07/05 17:29:15 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
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

/* THE MAIN STRUCT */

typedef struct	s_sashell 
{
	char	*command;
	char	**options;
	char	**arg;
	char	**red;
	int		in;
	int		out;
    
    int		ret;
	int		exit;
	int				no_exec;

	struct s_sashell	*next;
}				t_sashell;


/* parsing */

char	**protection_malloc2(char **str, int compt);
char	*protection_malloc1(char *str, int compt);
void    *ft_free(char **s, int i);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
int		ft_strlen(char *str);
int		ft_isalpha(int c);
void	ft_putstr(char *s);
void	ft_putchar(char c);

#endif