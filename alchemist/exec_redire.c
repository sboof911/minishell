#include "../minishell.h"

void 			reset_redirection(int *in, int *out, int *fd)
{
	dup2(*in, 0);
	dup2(*out, 1);
	close(*fd);
	close(*out);
	close(*in);
}

int 			exec_redirection(t_sashell *sashell, int *in, int *out, int *fd, int *index_in, int *index_out)
{
	int p = 0;
	char *file_name;

	if (sashell->red)
    {
		*in 	= dup(0);
		*out = dup(1);
        p = *index_out = *index_in = 0;
        while (sashell->red[p])
        {
			file_name = ft_strdup(sashell->red[p] + 3);
			
			if (sashell->red[p][1] == '<')
            {
				(*index_in)++;			  
				if ((*fd = open(file_name, O_RDONLY)) < 0)
				{
					printf("no such file or directory: %s\n", file_name);
					g_exit_value = 1;
					close(*fd);
					dup2(*in, 0);
					close(*in);
					free(file_name);
					return 1;
				}
				if ((dup2(*fd, 0 ) < 0))
				{
					ft_putstr("minishell: command not found: ");
					return 1;
				}
			}
	        else if (sashell->red[p][1] == '>')
            { 
				(*index_out)++;
				if (sashell->red[p][0] == '2')
					*fd = open(file_name,  O_WRONLY | O_APPEND | O_CREAT, 0777);
				else 
					*fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
				if (*fd < 0)
				{
					printf("no such file or directory: %s\n", file_name);
					g_exit_value = 1;
					close(*fd);
					dup2(*out, 1);
					close(*out);
					free(file_name);
					return 1;
				}
				if ((dup2(*fd, 1) < 0))
				{
					ft_putstr("minishell: command not found: ");
					g_exit_value = 1;
					close(*fd);
					dup2(*out, 1);
					close(*out);
					free(file_name);
					return 1;
				}
			}

			free(file_name);
           
		    p++;
        }
    }
	return 0;

}