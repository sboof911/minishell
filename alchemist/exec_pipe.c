#include "../minishell.h"

#define MAX_LINE 1024

// int	    exec_pipe(char *line, t_env *envs, t_sashell *sashell, int count)
// {
//    int  pfd[2];
//    int  status;
//    int  pid2;
//    int  pid;

//     /* parent process */


//     /* create  pipe */
//    if (pipe(pfd) == -1)
//     {
//         printf("pipe failed\n");
//         return 1;
//     }
     
//     /* child process1 */
//     if (((pid = fork()) == 0))
//     {
//         close(pfd[0]); /* close read side */
//         dup2(pfd[1], 1); /* redirect stdout to the write end of the pipe */
//         close(pfd[1]);
//         exec_cmd(sashell->tokens, envs, 2);
//         exit(EXIT_SUCCESS);
//     }
//     else if (pid < 0)
//     {
//         printf("fork failed\n");
//         return 2;
//     }

//     /* parent process */
//     sashell = sashell->next;
    




    
//     /* create the child 2 */
//     if ((pid2 = fork()) < 0)
//     {
//         printf("fork failed\n");
//         return 2;
//     }
//     /* child process2 */
//     if (pid2 == 0)
//     {
//         close(pfd[1]); /* close write side */
//         dup2(pfd[0], 0);
//         close(pfd[0]);
//         exec_cmd(sashell->tokens, envs, 2);
//         exit(EXIT_SUCCESS);
//     }
//     /* parent process */
//     close(pfd[0]);
//     close(pfd[1]);
//     waitpid(pid, &status, 0);
//     waitpid(pid2, &status, 0);

//     //printf("\nEnd Procees Pipe\n");
//     return 0;
// }

int     spawn_proc(int in, int out, t_env *envs,t_sashell *sashell)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }

      if (out != 1)
        {
          dup2 (out, 1);
          close (out);
        }
        exec_cmd(sashell->tokens, envs, 2);
        if (!pid)
            exit (EXIT_SUCCESS);
        return pid;
    }
  return pid;
}

int	    exec_pipe(char *line, t_env *envs, t_sashell *sashell, int count)
{
    int i;
    pid_t pid;
    int in, fd [2];
    int status;

    /* The first process should get its input from the original file descriptor 0.  */
    in = 0;
    int n = count;

    /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
    for (i = 0; i < n - 1; ++i)
    {
        pipe (fd);

        /* f [1] is the write end of the pipe, we carry `in` from the prev iteration.  */
        pid = spawn_proc (in, fd [1],envs, sashell);

        /* No need for the write end of the pipe, the child will write here.  */
        close (fd [1]);

        /* Keep the read end of the pipe, the next child will read from there.  */
        in = fd [0];
        sashell = sashell->next;
    }

    /* Last stage of the pipeline - set stdin be the read end of the previous pipe
        and output to the original file descriptor 1. */  
    if (in != 0)
        dup2 (in, 0);

    /* parent process */
    //sashell = sashell->next;
    
    pid_t pid2;
    /* create the child 2 */
    if ((pid2 = fork()) < 0)
    {
        printf("fork failed\n");
        return 2;
    }
    /* child process2 */
    if (pid2 == 0)
    {
        // close(fd[1]); /* close write side */
        // dup2(fd[0], 0);
        // close(fd[0]);
        exec_cmd(sashell->tokens, envs, 2);
        //exit(EXIT_SUCCESS);
    }
    /* parent process */
    // close(fd[0]);
    // close(fd[1]);
    wait(&status);
    printf("\nEnd Procees Pipe\n");
    return 0;
}

 