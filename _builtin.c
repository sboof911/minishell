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

t_env *ft_add_last_node(char *key, char *value)
{
	t_env *new;

	new = (t_env*)malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

int 	ft_export(char **cmd,t_env *env)
{
	int i = 0;
	char **name;
 	int index = 0;
    t_env *current_node = env;
	t_env *head = current_node;
	printf("\033[1;31m-------------------------------|     CMD     |--------------------------------------\033[0m\n\n");
	while (cmd[i])
		printf("- %s\n", cmd[i++]);
	printf("\033[1;31m-------------------------------| End of CMD  |--------------------------------------\033[0m\n\n");

	if (i == 1)
	{
		print(env); 
		return (0);
	}
	else
	{

		name = ft_split(cmd[1] ,'=');

		i = 0;
		while (name[i])
			printf("%s\n", name[i++]);
		printf("\n------------------------------\n");
		
		while (current_node) 
		{	

			printf("%s=%s\n", current_node->key, current_node->value);
			if (!current_node->next)
			{
				// printf("==================================");
				// printf("\nlast node = {%s=%s}\n", current_node->key, current_node->value);
			}
			current_node = current_node->next;
		}
		current_node = ft_add_last_node(name[0], name[1]);
		env = current_node;

		while (head)
		{
			printf("%s=%s\n", head->key, head->value);
			head = head->next;
		}
		return 1;
	}
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
