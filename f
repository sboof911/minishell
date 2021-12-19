minishell.c:52:54: error: unused parameter 'str' [-Werror,-Wunused-parameter]
void    minishell(t_sashell *sashell, t_env *env, char *str)
                                                        ^
minishell.c:89:27: error: unused parameter 'argv' [-Werror,-Wunused-parameter]
int     main(int argc, char **argv, char **envp)
                              ^
minishell.c:104:18: error: variable 'env' is uninitialized when used here [-Werror,-Wuninitialized]
        env = split_env(env, envp);
                        ^~~
minishell.c:93:13: note: initialize the variable 'env' to silence this warning
        t_env           *env;
                            ^
                             = NULL
3 errors generated.
sboof/outils/ft_substr.c:25:12: error: comparison of integers of different signs: 'unsigned int' and 'int' [-Werror,-Wsign-compare]
        if (start > ft_strlen((char *)s))
            ~~~~~ ^ ~~~~~~~~~~~~~~~~~~~~
1 error generated.
sboof/parsing/parsing_help.c:29:50: error: unused parameter 'tab' [-Werror,-Wunused-parameter]
t_sashell       *count_every(t_sashell *sashell, char *tab)
                                                       ^
1 error generated.
sboof/args/args.c:77:36: error: variable 'j' is uninitialized when used here [-Werror,-Wuninitialized]
                sashell = help_final(sashell, i, j);
                                                 ^
sboof/args/args.c:71:9: note: initialize the variable 'j' to silence this warning
        int                     j;
                                 ^
                                  = 0
1 error generated.
sboof/herdoc/herdoc.c:62:8: error: unused variable 'pid' [-Werror,-Wunused-variable]
        pid_t   pid;
                ^
1 error generated.
make: *** [minishell] Error 1
