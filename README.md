#  NOTES PART : EXECUTION  : 
 
 --segfault when change the path with cd and use env or export--  [solved]
 - g_exit_status [not-yet]



# Cmds :

> curl -fsSL https://raw.githubusercontent.com/hakamdev/42homebrew/master/install.sh | zsh

# Errors ; 

### in export 
  ** 1 **
> export env1=""
> export env1="exemple"
minishell(82240,0x1150815c0) malloc: *** error for object 0x7fa8ad500180: pointer being freed was not allocated
minishell(82240,0x1150815c0) malloc: *** set a breakpoint in malloc_error_break to debug