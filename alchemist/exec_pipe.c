#include "../minishell.h"

#define MAX_LINE 1024

void redirectIn(char *fileName)
{
    int in = open(fileName, O_RDONLY);
    dup2(in, 0);
    close(in);
}

void redirectOut(char *fileName)
{
    int out = open(fileName, O_WRONLY | O_TRUNC | O_CREAT, 0600);
    dup2(out, 1);
    close(out);
}

void run(char *args[])
{
    pid_t pid;
	int should_wait;
	int should_run;


    if (strcmp(args[0], "exit") != 0)
        {
            pid = fork();
            if (pid < 0) { 
                fprintf(stderr, "Fork Failed");
            }
            else if ( pid == 0) { /* child process */
                execvp(args[0], args);
            }
            else { /* parent process */
                if (should_wait) {
                    waitpid(pid, NULL, 0);
                } else {
                    should_wait = 0;
                }
            }
            redirectIn("/dev/tty");
            redirectOut("/dev/tty");
        }
    else {
        exit(0);
    }
}

void createPipe(char *args[])
{
    int fd[2];
    pipe(fd);
    dup2(fd[1], 1);
    close(fd[1]);
    //run(args);
    dup2(fd[0], 0);
    close(fd[0]);
}


static int    spwan_process(int in, int out, t_sashell *sashell, t_env *envs) {

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

       exec_cmd(sashell->tokens, envs);
    }

  return pid;
}

int	exec_pipe(char *line, t_env *envs, t_sashell *sashell, int count)
{
    int i = 0;
    int in = 0;
    int fd[2];
    printf("%d\n", count);
    while (i++ < count - 1)
    {
        pipe(fd);
        spwan_process(in, fd[1], sashell, envs);
        close(fd[1]);
        in = fd[0];
        sashell = sashell->next;
    }

    if (in != 0) {
        dup2(in, 0);
        
    }
    exec_cmd(sashell->tokens, envs);

}
 