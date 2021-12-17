/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:54:26 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/06 23:46:26 by amaach           ###   ########.fr       */
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

# define SKIP 		1
# define NOSKIP 	0

# define BUFF_SIZE 	4096
# define EXPANSION -36
# define ERROR 		1
# define SUCCESS 	0
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

# define INIT	-1
# define INIT	-1
# define QUOTE	39
# define DQUOTE	34
# define ETC	42
# define REDIR	62
# define DREDIR	6
# define BREDIR	60


int				 g_exit_value;
char			**g_envp;

typedef struct	s_token
{
	int 	token_count;

}				t_token;

typedef struct	s_quote
{
	int			type;
	int			start;
	int			end;
}				t_quote;


typedef struct	s_pipe
{
	char		*line;
	char		**argv;
}				t_pipe;

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
//	int  				***fd; /* fd[count][1 || 0][fd]*/
	int					error;
	int					count;
	int 			g_exit_value;

	struct s_sashell	*first;
	struct s_has		has;
	struct s_compt		compt;
	struct s_sashell	*next;
}					t_sashell;

/* --------------------- libft outils ------------------------------*/
char	    	**protection_malloc2(char **str, int compt);
char	    	*protection_malloc1(char *str, int compt);
void	    	*ft_free(char **s, int i);
char	    	**ft_split(char const *s, char c);
char	    	*ft_strdup(const char *s);
int		    	ft_strlen(char *str);
int		    	ft_isalpha(int c);
int				ft_isalnum(int c);
void	    	ft_putchar(char c);
void	    	ft_putstr(char *s);
char			*ft_charjoin(char *str, char c);
char	    	*ft_strjoin(char *s1, char *s2);
void	    	ft_putnbr(int n);
char	    	*ft_strchr(const char *s, int c);
char	    	*ft_substr(char const *s, unsigned int start, size_t len);
int		    	ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_itoa(int n);
char			*ft_strrev(char *str);

/* --------------------- parsing outils ------------------------------*/
char	    	**split_pipe(char const *s, char c);
int				ft_count_tab(char **tab);
void			free_sashell(t_sashell *sashell);

/* --------------------- parsing ------------------------------*/
t_sashell		*command_parse(t_sashell *sashell, char **tab, t_env *env);
t_sashell		*count_every(t_sashell *sashell, char *tab);
t_sashell		*initialize(t_sashell *sashell);
t_sashell		*fill_in_the_blank(t_sashell *sashell, char *tab, t_env *env);
t_sashell		*next_sashell(t_sashell *sashell, t_env *env, char **tab);
t_sashell		*parse_time(char **tab, t_env *env);
char			**delete_spaces(char **tab);
t_sashell		*parse_function(t_sashell *sashell, t_env *env, char *line);


/* --------------------- rederiction ------------------------------*/
t_sashell		*check_file(t_sashell *sashell, char *tab, int i);
int				count_quotes(char *tab);
char			*delete_quotes(char *tab);
t_sashell		*rederiction_parse(t_sashell *sashell, char *tab, char red);
char			rederiction_sign(char *tab);
int				help_rederiction(t_sashell *sashell, char **tab, int i);
int				help_red(char **tab, int i, t_sashell *sashell, int remember);
t_sashell		*parse_red(t_sashell *sashell, char **tab, int i, int remember);

/* --------------------- dollar ------------------------------*/
t_sashell		*dollar_parse(t_sashell *sashell, char *tab, t_env *env);
int				help_num_dollar(t_sashell *sashell, char *tab, int i);
int				help_check_dollar(t_sashell *sashell, char *tab, t_env *env, int i);
int				help_dollar_quotes(int d_q);
t_sashell		*help_norm_dollar(t_sashell *sashell, char *tab, int i);
int				some_shit(int *d_quotes, int *s_quotes, char *tab, int i);
t_sashell		*check_dollar(t_sashell *sashell, char *tab, t_env *env, int i);

/* --------------------- args ------------------------------*/
t_sashell		*arg_parse(t_sashell *sashell, char **tab, t_env *env);

/* --------------------- Errors parsing ------------------------------*/
int				check_red(char *line, int i);
int				check_quotes(char *line);
int				help_check_pipe(char *line, int i, int compt1, int compt2);
int				check_pipe(char *line, int i, int pipe, int compt1);
int				help_check_sytax(char *line, int i);
int				check_sytaxerr(char *line);

/* --------------------- Herdoc ------------------------------*/
char			*generate_random_value(void);
void			quit_handler(int num);
void			quit_handlerherdoc(int num);
char			*heredoc(t_sashell *sashell, int i);
t_sashell		*red_open(t_sashell *sashell);

/* --------------------- signals ------------------------------*/
void			quit_handler(int num);

/* --------------------- exec_others ------------------------------*/
void			free_double_arr(char **arr);
void			free_env(t_env *env);
int				ft_puterror_fd(char *s1, char *s2, int fd);
int				is_exist_keyy(char *key, t_env *envs);
char			*find_valuee(char *key, t_env *envs);
char			*find_path(char *argv, t_env *envs);
void			exec_others(char **cmd, t_env *envs, char **g_envp);

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

static int		add_env_or_modify_value(int index, char **argv, t_env **envs);
void			sort_double_arr(char **arr);
static void		update_value(t_env *env, t_env **envs);
void			add_declare_for_export(char **arr);
char 			**convert_env_to_arr(t_env *lst) ;
void 			ft_export(char **cmd, t_env *env);

/* ---------------------------- cmd_unset -------------------------- */

void			ft_unset(char **argv, t_env *envs);
static void		delete_key(char *argv, t_env *envs);

/* ---------------------------- cmd_exit -------------------------- */
void			ft_exit(char **argv);
static int		ft_isdigit_str(char *str);
int				ft_atoi(const char *str);

/* ---------------------------- exec_pipe -------------------------- */
// void			exec_pipe(char *line, t_env *envs, t_sashell *sashell);
int				exec_pipe(char *line, t_env *envs, t_sashell *sashell, int count);
 int			has_redir(char *str);

/* ---------------------------- exec_redir -------------------------- */
void			exec_redir(char *line, t_env *envs);

void 			exec_cmd(t_sashell *sashell, char **cmd, t_env *env, int i);
void 			print_sashell(t_sashell *sashell);
void			execo_others(char **cmd, t_env *envs, char **g_envp);


#endif
