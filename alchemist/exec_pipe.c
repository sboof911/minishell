#include "../minishell.h"

void	exec_pipe(char *line, t_env *envs, t_sashell *sashell)
{
	int		fd[2];
	int		child[2];
	int		status[2];


	printf("%s || %d || %d \n", line, sashell->compt.tokens, sashell->count) ;



}
 