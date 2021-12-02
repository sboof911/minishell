#  NOTES PART : EXECUTION  : 
 
 --segfault when change the path with cd and use env or export--  [solved]
 - g_exit_status [not-yet]

## EXECUTION SIDE TASKS:
** ---------------------------------------------- ** 
## BUILT-INS

 - ##### cd            [done]
 - ##### export        [done]

< case when there is an existent env key="value" when i do export m="", the value must not update  >

 - ##### echo + -n     [done]
 - ##### pwd           [done]
 - ##### unset         [done]
 - ##### exit          [done]

** ---------------------------------------------- ** 
## Search and launch the right executable (based on the PATH variable or by using relative or absolute path) 
  ##### - [next_step]

** ------------------------------------------------**
## return each program executed

  - ##### global variable g_exit_value or sashell->g_exit_value
  

** ---------------------------------------------- ** 
## Redirections:
   ##### ◦ < should redirect input.
   ##### ◦ > should redirect output.
   ##### ◦ “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
   ##### ◦ “>>” should redirect output with append mode.

** ---------------------------------------------- ** 
## • ctrl-C ctrl-D ctrl-\ should work like in bash. 
  ### When interactive:
   ##### ◦ ctrl-C print a new prompt on a newline.
   ##### ◦ ctrl-D exit the shell.
   ##### ◦ ctrl-\ do nothing.
** ---------------------------------------------- **  

**  Errors **

bash-3.2$ 1 > 2 > 3 > 4
bash: 1: command not found
bash-3.2$ 


** check
