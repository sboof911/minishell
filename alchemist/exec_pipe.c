#include "../minishell.h"

int	    exec_pipe(char *line, t_env *envs, t_sashell *sashell, int count)
{
  int     pfd[2];
  int     status;
  pid_t   pid[count -1];
  int     tmp_fd = 0;
  int p = 0;
  /* parent process */
  int i = 0;
  int j =0;
/*
              0 -> STDIN 
              1 -> STDOUT
              
    fd[0] -> read
    fd[1] -> write
*
pipe2 read from stdin
pipe2 write to stdout
*/

  int index_in = 0;
  int index_out = 0;

  while (i < count) 
  {

      /*create  pipe*/
      if (pipe(pfd) == -1)
        {
            printf("pipe failed\n");
            return -1;
        }
      /*create the child*/
      if ((pid[i] = fork()) < 0)
        {
          printf("fork failed\n");
          return -2;
        }
      /*child process*/
      if (pid[i] == 0)
        {

          /* handiling input */
          if (i != 0)
            {
                dup2(tmp_fd, 0);
                close(tmp_fd);
            }
            close(pfd[0]);
        

          /* handling output */ 
          if (i != count - 1)
                dup2(pfd[1], 1);
          close(pfd[1]);


          exec_cmd(sashell, sashell->tokens, envs, 2);
          exit(EXIT_FAILURE);
        }
      if (tmp_fd != 0)
          close(tmp_fd);

      sashell = sashell->next;
      i++;
      tmp_fd = pfd[0];
      close(pfd[1]);
  }

  close(pfd[0]);
  i = 0;
  while (i < count)
    waitpid(pid[i++], &status, 0);
  g_exit_value = status;
  return g_exit_value;
}