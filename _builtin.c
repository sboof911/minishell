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

t_env 	*ft_export(char **cmd,t_env *env)
{
	int i = 0;
	char **name;
	t_env* last = env;
	t_env* new_node;
	int y = 0;


	/* count commande + args */
	while (cmd[i])
		i++;

	/* if only there is "export " without args */
	if (i == 1)
	{
		print(env); 
		return (env);
	}
	else if (i > 1)
	{
		t_env* new_node = ( t_env*)malloc((sizeof(env)));
		while(cmd[++y])
		{
			// look for "=" if exist in cmd[y]
			if (!ft_strrchr(cmd[y], '='))
				return (NULL);
		
			// parse each argument 'key=value'
			name = ft_split(cmd[y] ,'=');
			// count all keys and values
			i = 0;
			while (name[i])
				i++;
			/* protect case "mehdi=mehdh=d"	*/
			if (i < 1 && i > 1)
				return NULL;
			/* putting data */
			new_node->key = name[0];
			new_node->value = name[1];
			new_node->next = NULL;
			while (last->next != NULL)
				last = last->next;
			last->next = new_node;
			while (last->next != NULL)
				last = last->next;
			last->next  = NULL;
		}
	}	
	return env;


	// parse each argument 'key=value'
	//name = ft_split(cmd[1] ,'=');

	/*   update if its already exist */


	/* add it if it's doesn't exist */

/*.........................................*/
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
		env = ft_export(cmd , env);

	if (!env)
		return -1;

	//printf("------- all envs ---------\n");
	//print(env);
	
	return result;
}
