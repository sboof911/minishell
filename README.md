# 1337 cursus Project : minishell 
taking bash as a reference to made a little nasty one that include : 
- 1 
- 2
- 3
- 4
- 5 
 
## Cmds :

> curl -fsSL https://raw.githubusercontent.com/hakamdev/42homebrew/master/install.sh | zsh


## to do liste  : 

+ [_] handle absolute path case 1 
+ [_] review export  case 2 
+ [_] handle the exit status  g_exit_status 
+ [_] handle filename with spaces like case 4 
+ [_] handle echo -nnnn case 3 
+ [_] review quote and double quotes on cases 3 
+ [_] handle parsing when cmd< input || cmd> output   

## ERRORS:

### case 1 :

- -- ABSOLUTE COMMANDE LIKE /bin/ls

### case 2 :

- export env1="".  
- export env1="exemple"

minishell(82240,0x1150815c0) malloc: *** error for object 0x7fa8ad500180: pointer being freed was not allocated
minishell(82240,0x1150815c0) malloc: *** set a breakpoint in malloc_error_break to debug

- case export [] 

export mehdi
export mehdi=p
~/Users/eelaazmi/Desktop/minishell $> env 

### case 3 :

- echo -nnn mm

- echo '0' 'a' | cat -e

- 'e'"c"h"o" hi | cat -e

- echo '"   " adsjhfgjadhsf ha '

### case 4 :

- ls < input > output | ls < iSn DFSDF > o [DO NOT HANDLE THIS PSYCHOPATE CASE]
<br>

#### sashel STDOUT
<br>
=============================|     Tokens    |========================================
*********************************
pipe[1]...tokens[0] = ls
pipe[1]...red[0] = 1< input
pipe[1]...red[1] = 1> output
*********************************
pipe[2]...tokens[0] = ls
pipe[2]...tokens[1] = DFSDF
pipe[2]...red[0] = 1< iSn
pipe[2]...red[1] = 1> o
*********************************
1

=============================| End of Tokens |========================================

redir0 |{<}| 1< input
redir0 |{>}| 1> output

redir1 |{<}| 1< iSn
redir1 |{>}| 1> o

*case end*
<br>

### case 5 :

- ls< README.md 


