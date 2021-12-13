#include <unistd.h>


static int    spawn_proc(int in, int out, t_sashell *sashell, t_env *envs) {

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
        printf("exec pid=%d cmd\n", getpid());
        exec_cmd(sashell->tokens, envs);
        printf("excec cmd? done\n");

      return pid;
    }

  return pid;
}

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
struct command
{
  const char **argv;
};

int
spawn_proc(int in, int out, struct command *cmd)
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

      return execvp (cmd->argv [0], (char * const *)cmd->argv);
    }

  return pid;
}

int
fork_pipes (int n, struct command *cmd)
{
  int i;
  pid_t pid;
  int in, fd [2];

  /* The first process should get its input from the original file descriptor 0.  */
  in = 0;

  /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
  for (i = 0; i < n - 1; ++i)
    {
      pipe (fd);

      /* f [1] is the write end of the pipe, we carry `in` from the prev iteration.  */
      spawn_proc (in, fd [1], cmd + i);

      /* No need for the write end of the pipe, the child will write here.  */
      close (fd [1]);

      /* Keep the read end of the pipe, the next child will read from there.  */
      in = fd [0];
    }

  /* Last stage of the pipeline - set stdin be the read end of the previous pipe
     and output to the original file descriptor 1. */  
  if (in != 0)
    dup2 (in, 0);

  /* Execute the last stage with the current process. */
  return execvp (cmd [i].argv [0], (char * const *)cmd [i].argv);
}



int
main ()
{
  const char *ls[] = { "ls", "-l", 0 };
  const char *awk[] = { "grep", "l", 0 };
//   const char *sort[] = { "sort", 0 };
//   const char *uniq[] = { "uniq", 0 };

  struct command cmd [] = { {ls}, {awk} };

  return fork_pipes (2, cmd);
}