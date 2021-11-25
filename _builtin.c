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

char *ft_strl(char *s, size_t len)
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

t_env 	*ft_export(char **cmd,t_env *env)
{
	int i = 0;
	char **name;
	t_env* last = env;
	t_env* new_node;
	int y = 0;
	int u = 0;

    /* count commande + args */
	while (cmd[i])
		i++;

	/* if only there is "export " without args */
	if (i == 1)
	{
		print(env); /* change the print to be like in the bash*/
		return (env);
	}
	else if (i > 1)
	{
		while(cmd[++y])
		{
			// look for "=" if exist in cmd[y]
			if (!ft_strrchr(cmd[y], '='))
				return (NULL);

			// case "=env" an error
			if (cmd[y][0] == '=')
				return (NULL);
			
			// parse each argument 'key=value'			
			/* parse by taking the first '=' to be in the key and the rest to be in the value */
			u = 0;
			while (cmd[y][u] != '='  && cmd[y][u] != '\0')
				u++;

			name[0] = ft_strl(cmd[y], u);
			u++;
			name[1] = ft_strl((cmd[y]) + u, strlen(cmd[y]) - u);
			printf("[%s]=[%s]\n",name[0],  name[1]);

			new_node = ( t_env*)malloc((sizeof(env)));




			/*   update if its already exist */


			/* add it if it's doesn't exist */

			/* putting data */
			new_node->key = name[0];

			/* case if no value setted to the key "env="*/
			if (name[1] != NULL)
				new_node->value = name[1];
			else
				new_node->value = "";
			new_node->next = NULL;

			/* to last node */
			while (last->next != NULL)
				last = last->next;
			last->next = new_node;

			while (last->next != NULL)
				last = last->next;
			last->next = NULL;

		}
	}	
	return last;



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
