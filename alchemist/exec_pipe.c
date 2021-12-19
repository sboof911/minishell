#include "../minishell.h"

int	    exec_pipe(char *line, t_env *envs, t_sashell *sashell, int count)
{
  int     pfd[2];
  int     status;
  pid_t   pid[count];
  int     tmp_fd = 0;
  int p = 0;
  int i = 0;
  int j =0;
  int index_in = 0;
  int index_out = 0;
	char *file_name;
	int fd = 0;
	int in, out;

  while (i < count) 
  {
      /*create  pipe*/
      if (pipe(pfd) == -1)
        {
            printf("pipe failed\n");
            return -1;
        }
      /*create the child*/
      if ( (i < count) && (pid[i] = fork()) < 0)
        {
          printf("fork failed\n");
          return -2;
        }
      /*child process*/
      if (pid[i] == 0)
        {         
        /* DO REDIRECTIONS*/
          if (sashell->red)
            {
              in 	= dup(0);
              out = dup(1);
              p = index_out = index_in = 0;
              while (sashell->red[p])
              {
                file_name = ft_strdup(sashell->red[p] + 3);
                if (sashell->red[p][1] == '<')
                {
                    index_in++;			  
                    if ((fd = open(file_name, O_RDONLY)) < 0)
                    {
                      printf("no such file or directory: %s\n", file_name);
                      g_exit_value = 1;
                      close(fd);
                      dup2(in, 0);
                      close(in);
                      free(file_name);
                      return-1;
                    }
                    if ((dup2(fd, tmp_fd) < 0))
                    {
                      ft_putstr("minishell: command not found: ");
                      return-1;
                    }
                }
              
                else if (sashell->red[p][1] == '>')
                { 
                    index_out++;
                  if ((fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600)) < 0)
                  {
                    printf("no such file or directory: %s\n", file_name);
                    g_exit_value = 1;
                    close(fd);
                    dup2(out, 1);
                    close(out);
                    free(file_name);
                    return-1;
                  }
                  if ((dup2(fd, 1) < 0))
                  {
                    ft_putstr("minishell: command not found: ");
                    g_exit_value = 1;
                    close(fd);
                    dup2(out, 1);
                    close(out);
                    free(file_name);
                    return-1;
                  }
                }
                free(file_name);
                p++;
              }
            }         
          p =  0;

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