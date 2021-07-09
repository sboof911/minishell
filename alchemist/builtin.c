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

int		ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		printf("%s\n", cwd);
		return (SUCCESS);
	}
	else
		return (ERROR);
}

int exec_builtin(char **cmd)
{
	int result = 0;

	if (!strcmp(cmd[0], "pwd"))
		result = ft_pwd();


	return result;
}
