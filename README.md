# 1337 cursus Project : minishell 
taking bash as a reference to made a little nasty one that include : 
- 1 
- 2
- 3
- 4
- 5 
 
## Cmds :

> curl -fsSL https://raw.githubusercontent.com/hakamdev/42homebrew/master/install.sh | zsh

> sudo apt-get install lib32readline8 lib32readline-dev libreadline-dev ; gcc $(SRCS) -L/usr/local/lib -I/usr/local/include -lreadline -o $(NAME) 

## to do liste  : 

+ [_] handle the exit status  g_exit_status 

+ echo $?                                                                   [CHECK]


+ [_] handle absolute path case 1 
    - [_] handle the token {/path/bin/exemple} -> parsing                   [CHECK]
    - [_] executed the absolute and relatibve path tokens -> execution 



------------------------------------------------

+ [_] handle filename with spaces like case 4 
+ [_] review quote and double quotes on cases 3 
+ [_] handle parsing when cmd< input || cmd> output

## ERRORS:

### case 1 :

- -- ABSOLUTE COMMANDE LIKE /bin/ls                                         [CHECK]

### case 3 :

- echo -nnn mm                                                              [CHECK]

- echo '0' 'a' | cat -e                                                     [CHECK]

- 'e'"c"h"o" hi | cat -e                                                    [CHECK]

- echo '"   " adsjhfgjadhsf ha '                                            [BONUS]

### case 4 :

- ls < input > output | ls < iSn DFSDF > o [DO NOT HANDLE THIS PSYCHOPATE CASE]
- ls < input > output | ls < "iSn DFSDF" > o                                [CHECK]
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

### case 6 :
#### parsing
echo -   "asdasdasdas "dasas "dsadas "                                      [CHECK]
ls -l | cat '"Makefile"'                                                    [CHECK]
#### execution
export po | env 
