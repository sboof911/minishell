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


void	exec_pipe(char *line, t_env *envs, t_sashell *sashell, int count)
{
	int		fd[2];
	int		child[2];
	int		status[2];
    pid_t   pid, pid2;
	int 	index = 0;
	int i =0;

	// while (sashell)
	// {
		//createPipe(sashell->tokens);

        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        if ((pid = fork()) < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            dup2(fd[1], 1);
            close(fd[1]);
            close(fd[0]);
            exec_cmd(sashell->tokens, envs);
            return ;

        }

        else if ((pid = fork()) < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else 
        {
            printf("%d\n", pid);
        }
        // }

        close(fd[1]);
        close(fd[0]);
        waitpid(pid, NULL, 0);
    //    waitpid(pid2, NULL, 0);
        exit(0);
}
 