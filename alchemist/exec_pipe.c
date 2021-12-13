#include "../minishell.h"

#define MAX_LINE 1024

int	    exec_pipe(char *line, t_env *envs, t_sashell *sashell, int count)
{
   int  pfd[2];
   int  status;
   int  pid2;
   int  pid;

    /* parent process */


    /* create  pipe */
   if (pipe(pfd) == -1)
    {
        printf("pipe failed\n");
        return 1;
    }
     
    /* child process1 */
    if (((pid = fork()) == 0))
    {
        close(pfd[0]); /* close read side */
        dup2(pfd[1], 1); /* redirect stdout to the write end of the pipe */
        close(pfd[1]);
        exec_cmd(sashell->tokens, envs, 2);
        exit(EXIT_SUCCESS);
    }
    else if (pid < 0)
    {
        printf("fork failed\n");
        return 2;
    }

    /* parent process */
    sashell = sashell->next;
    




    
    /* create the child 2 */
    if ((pid2 = fork()) < 0)
    {
        printf("fork failed\n");
        return 2;
    }
    /* child process2 */
    if (pid2 == 0)
    {
        close(pfd[1]); /* close write side */
        dup2(pfd[0], 0);
        close(pfd[0]);
        exec_cmd(sashell->tokens, envs, 2);
        exit(EXIT_SUCCESS);
    }
    /* parent process */
    close(pfd[0]);
    close(pfd[1]);
    waitpid(pid, &status, 0);
    waitpid(pid2, &status, 0);

    //printf("\nEnd Procees Pipe\n");
    return 0;
}

 