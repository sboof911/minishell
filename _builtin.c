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

int 	ft_error(char *s)
{
	printf("%s\n",s);
	//exit(-1);
	return -1;
}

char	*ft_strrchr(const char *str, int c)
{
	char	*s;
	int		len;

	s = (char *)str;
	len = strlen(str);
	s += len;
	while (len >= 0)
	{
		if (*s == (char)c)
			return (s);
		s--;
		len--;
	}
	return (0);
}

char 	*ft_strl(char *s, size_t len)
{
	char *str;
	size_t i;

	i = 0;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	 	exec_builtin(char **cmd, t_env *env)
{
	int result = 0;

	if (!strcmp(cmd[0], "pwd"))
		result = ft_pwd();
	else if (!strcmp(cmd[0], "echo"))
		result = ft_echo(cmd, 1);
	else if (!strcmp(cmd[0], "cd"))
		result = ft_cd(cmd, env);
	else if (!strcmp(cmd[0], "env"))
		result = print(env);

	else if (!strcmp(cmd[0], "export"))
		ft_export(cmd, env);

		//env = ft_export(cmd , env);

	if (!env)
		return -1;

	//printf("------- all envs ---------\n");
	//print(env);
	
	return result;
}
