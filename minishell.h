/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eelaazmi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:54:26 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/11/27 17:54:29 by eelaazmi         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>

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

int g_exit_value;

typedef struct	s_has
{
	int		red;
	int		arg;
	int		option;
}				t_has;

typedef struct s_compt
{
	int		red;
	int		dollar;
	int		tokens;
	int		position;
}				t_compt;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_sashell 
{
	char				**tokens;
	char				**red;
	int					error;
	int					count;
	int g_exit_value;

	struct s_sashell	*first;
	struct s_has		has;
	struct s_compt		compt;
	struct s_sashell	*next;
}				t_sashell;

char	    **protection_malloc2(char **str, int compt);
char	    *protection_malloc1(char *str, int compt);
void	    *ft_free(char **s, int i);
char	    **ft_split(char const *s, char c);
char	    **split_pipe(char const *s, char c);
char	    *ft_strdup(const char *s);
int		    ft_strlen(char *str);
int		    ft_isalpha(int c);
int			ft_isalnum(int c);
void	    ft_putstr(char *s);
void	    ft_putchar(char c);
char		*ft_charjoin(char *str, char c);
char	    *ft_strjoin(char *s1, char *s2);
void	    ft_putnbr(int n);
char	    *ft_strchr(const char *s, int c);
char	    *ft_substr(char const *s, unsigned int start, size_t len);
int		    ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_count_tab(char **tab);
void		free_sashell(t_sashell *sashell);
char		*ft_itoa(int n);
char		*ft_strrev(char *str);
t_sashell	*parse_function(t_sashell *sashell, t_env *env, char *line);


/*	tool execution */


/* ----------------------- 	ft_echo	------------------------------ */

void			ft_putstr_fd(char *s, int fd);
int 			nb_args(char **argv);
int				ft_echo(char **args, int fd);

/* ----------------------- 	ft_pwd	------------------------------ */

int				ft_pwd(void);

/* ----------------------- 	ft_cd	------------------------------ */
void 			ft_cd(char  **cmd, t_env *env);


/* ----------------------- 	tools	------------------------------ */

char			*ft_sstrjoin(char const *s1, char const *s2);
void			*ft_memdel(void *ptr);
void			ft_putendl_fd(char *s, int fd);
int 			print(t_env *head);
char			*ft_strrchr(const char *str, int c);

/* ----------------------- 	ft_cd	------------------------------ */

static void		print_error(char **args);
int				ft_pwd(void);
int 			nb_args(char **argv);
void			ft_putstr_fd(char *s, int fd);
char			*ft_substr(const char *str, unsigned int start, size_t len);
char			*ft_strchr(const char *str, int c);
int				ft_isdigit(int c);

/* -------------------------- _builtin ------------------------------- */

int				is_builtin(char *command);
char 			*ft_strl(char *s, size_t len);
int     		exec_builtin(char **cmd, t_env *env);


/* ---------------------cmd_export_outils export --------------------- */

char			*ft_sdtrjoin(const char *s1, const char *s2);
int				ft_lstsize(t_env *lst);
void			print_arr(char **arr);
void			free_arr(char **arr);
int				is_valid_env(char *arg);
int				is_exist_key(char *key, t_env *envs);
void	    	ft_lstadd_back(t_env **lst, t_env *new);
t_env	    	*ft_lstnew(t_env *content);
char			*ft_ssubstr(char const *s, unsigned int start, size_t len);


/* ---------------------------- cmd_export -------------------------- */

static void		add_env_or_modify_value(char **argv, t_env **envs);
void			sort_double_arr(char **arr);
static void		update_value(t_env *env, t_env **envs);
void			add_declare_for_export(char **arr);
static void		add_env_or_modify_value(char **argv, t_env **envs);
char 			**convert_env_to_arr(t_env *lst) ;
void 			ft_export(char **cmd, t_env *env);

/* ---------------------------- cmd_unset -------------------------- */

void			ft_unset(char **argv, t_env *envs);
static void		delete_key(char *argv, t_env *envs);

/* ---------------------------- cmd_exit -------------------------- */
void			ft_exit(char **argv);
static int		ft_isdigit_str(char *str);
int				ft_atoi(const char *str);

#endif
