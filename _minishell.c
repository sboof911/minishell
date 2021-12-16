/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _minishell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 17:50:55 by eelaazmi          #+#    #+#             */
/*   Updated: 2021/12/07 15:39:05 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env			*fill_env(t_env *env, char *envp)
{
	char	**help;

	help = ft_split(envp, '=');
	env->key = ft_strdup(help[0]);
	env->value = ft_strdup(help[1]);
	ft_free(help, 0);
	return (env);
}

t_env			*split_env(t_env *env, char **envp)
{
	t_env	*tmp;
	int		i;

	env = (t_env *)malloc(sizeof(t_env));
	i = 1;
	env = fill_env(env, envp[0]);
	tmp = env;
	env->next = (t_env *)malloc(sizeof(t_env));
		if (!env->next)
			return (NULL);
	env = env->next;
	while (envp[i])
	{
		env = fill_env(env, envp[i]);
		if (envp[i + 1])
		{
			env->next = (t_env *)malloc(sizeof(t_env));
			if (!env->next)
				return NULL;
			env = env->next;
		}
		i++;
	}
	env->next = NULL;
	env = tmp;
	return (env);
}

void 			print_sashell(t_sashell *sashell)
{
	int i = 0;
	t_sashell	*tmp;
	int compt;

	tmp = sashell;
	compt = 1;
	while (sashell)
	{
		i = -1;
		printf("*********************************\n");
		while (sashell->tokens[++i])
			printf("pipe[%d]...tokens[%d] = %s\n", compt, i, sashell->tokens[i]);
		i = -1;
		while (sashell->red[++i])
			printf("pipe[%d]...red[%d] = %s\n", compt, i, sashell->red[i]);
		sashell = sashell->next;
		compt++;
	}
	printf("*********************************\n");
	sashell = tmp;
}

void			free_sashell(t_sashell *sashell)
{
	t_sashell	*tmp;
	int			i;

	i = 0;
	while (sashell)
	{
		tmp = sashell->next;
		ft_free(sashell->tokens, 1024);
		ft_free(sashell->red, 1024);
		free(sashell);
		sashell = tmp;
	}
	// free(sashell);
}

int				ft_token_count(t_token *token, t_sashell *sashell)
{
	while (sashell)
	{
		token->token_count++;
		sashell = sashell->next;
	}
	return (token->token_count);
}

void 			exec_cmd(t_sashell *sashell, char **cmd, t_env *env, int i)
{
	int ret;
	int index_in = 0, index_out = 0;
	int p = 0;
	char *file_name;
	int fd = 0;
	int in, out;

	/* DO REDIRECTIONS*/
	if (sashell->red)
    {
		in 	= dup(0);
		out = dup(1);
        p = index_out = index_in = 0;
        while (sashell->red[p])
        {
			file_name = ft_strdup(sashell->red[p] + 3);
			
			if (sashell->red[p][1] == '<')
            {
				index_in++;			  
				if ((fd = open(file_name, O_RDONLY)) < 0)
				{
					printf("no such file or directory: %s\n", file_name);
					g_exit_value = 1;
					close(fd);
					dup2(in, 0);
					close(in);
					free(file_name);
					return;
				}
				if ((dup2(fd, 0 ) < 0))
				{
					ft_putstr("minishell: command not found: ");
					return;
				}
			}
       
	        else if (sashell->red[p][1] == '>')
            { 
				index_out++;
				//printf("write to {%s}\n", sashell->red[p] + 3);
				if ((fd = open(file_name, O_WRONLY | O_TRUNC | O_CREAT, 0600)) < 0)
				{
					printf("no such file or directory: %s\n", file_name);
					g_exit_value = 1;
					close(fd);
					dup2(out, 1);
					close(out);
					free(file_name);
					return;
				}
				if ((dup2(fd, 1) < 0))
				{
					ft_putstr("minishell: command not found: ");
					g_exit_value = 1;
					close(fd);
					dup2(out, 1);
					close(out);
					free(file_name);
					return;
				}
			}

			free(file_name);
           
		    p++;
        }
    }
	
	/* EXECUTION */
	if (cmd && is_builtin(cmd[0]))
		ret = exec_builtin(cmd, env);
	else if (cmd && i > 1)
		exec_others(cmd, env, g_envp);
	else if (cmd && i == 1)
		execo_others(cmd, env, g_envp);
	else
		ft_putstr("minishell: command not found: ");
	
	/* RESET STDIN STDOUT */
	if (index_in || index_out)
	{
		dup2(in, 0);
		dup2(out, 1);
		close(fd);
		close(out);
		close(in);
	}
}


void			minishell(t_sashell *sashell, t_env *env, char *str)
{
	char 		**cmd;
	int 		ret;
	int 		index;
	t_token 	token;

	index = 0;
	token.token_count = 0;
	cmd = sashell->tokens;
	sashell->g_exit_value = 0;

	ft_token_count(&token, sashell);
	if (token.token_count > 1)
		exec_pipe(str, env, sashell, token.token_count);
	else if (cmd)
	 	exec_cmd(sashell, cmd, env, 1);
}

int		main(int argc, char **argv, char **envp)
{
	char		*line;
	t_sashell	*sashell;
	t_env		*env;
	char		cwd[PATH_MAX];

	g_envp = envp;
	signal(SIGQUIT, &quit_handler);
	signal(SIGINT, &quit_handler);
	env = split_env(env, envp);
	while (1)
	{
		getcwd(cwd, PATH_MAX);
		printf("\e[48;5;098m~%s", cwd);

		line = readline("\e[48;5;098m $> \033[0m");
		if (line == NULL)
			break ;
		if (strcmp(line , "") == 0)
			continue;
		else
		{
			add_history(line);
			sashell = parse_function(sashell, env, line);
			if (sashell)
			{
				// printf("\n\033[1;33m=============================|     Tokens    |========================================\033[0m\n");
				// print_sashell(sashell);
				// printf("%d\n", sashell->compt.tokens);
				// printf("\n\033[1;33m=============================| End of Tokens |========================================\033[0m\n\n");
				// main-execution-process

				minishell(sashell, env, line);
				free_sashell(sashell);
			}
			// system("leaks minishell");
		}
	}
	free_env(env);
	return (0);
}
