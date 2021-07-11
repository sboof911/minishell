#include "../sboof/minishell.h"



int		is_builtin(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (1);
	if (strcmp(command, "cd") == 0)
		return (1);
	if (strcmp(command, "pwd") == 0)
		return (1);
	if (strcmp(command, "env") == 0)
		return (1);
	if (strcmp(command, "export") == 0)
		return (1);
	if (strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

int exec_builtin(char **cmd, t_env *env)
{
	int result = 0;

	if (!strcmp(cmd[0], "pwd"))
		result = ft_pwd();

	if (!strcmp(cmd[0], "echo"))
		result = ft_echo(cmd);

	if (!strcmp(cmd[0], "cd"))
		result = ft_cd(cmd, env);
	


	return result;
}
