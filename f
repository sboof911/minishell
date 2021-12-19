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
