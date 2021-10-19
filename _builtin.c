#include "minishell.h"



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

int ft_error(char *s)
{
	printf("%s\n",s);
	//exit(-1);
	return -1;
}

int 	ft_export(char **cmd,t_env *env)
{
	int i = 0;
	char **name;
 	int index = 0;

	while (cmd[i])
		printf("%s\n", cmd[i++]);

	if (i > 2)
		return ft_error("Error: invalid parametre");
	if (i == 1)
		{
			print(env);
			return (1);
		}
	name = ft_split(cmd[1], '=');

	i = 0;

	while (name[i])
		printf("%s | ", name[i++]);

	if (i <= 1)
		name[i] = "";

	/* check if the key of env already exist if yes the replace the value if no wait until the last key then change it */

 	return 1;
}

int exec_builtin(char **cmd, t_env *env)
{
	int result = 0;

	if (!strcmp(cmd[0], "pwd"))
		result = ft_pwd();
	else if (!strcmp(cmd[0], "echo"))
		result = ft_echo(cmd);
	else if (!strcmp(cmd[0], "cd"))
		result = ft_cd(cmd, env);
	else if (!strcmp(cmd[0], "env"))
		result = print(env);

	else if (!strcmp(cmd[0], "export"))
		result = ft_export(cmd ,env);

	return result;
}
