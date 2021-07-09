/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:10:34 by amaach            #+#    #+#             */
/*   Updated: 2021/07/08 15:03:53 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sboof/minishell.h"
#include <string.h>

typedef struct	s_has
{
	int		red;
	int		arg;
	int		option;
}				t_has;

typedef struct s_compt
{
	int		red;
	int		dollar;
	int		tokens;
	int		position;
}				t_compt;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct	s_sashell 
{
	char				**tokens;
	char				**red;
	int					in;
	int					out;
	struct s_has		has;
	struct s_compt		compt;
	struct s_sashell	*next;
}				t_sashell;

t_sashell	*check_file(t_sashell *sashell, char **tab, int i)
{
	if (ft_strlen(tab[sashell->compt.position]) <= 2 &&
		(tab[sashell->compt.position][1] == '>' || tab[sashell->compt.position][1] == '<'
		|| ft_strlen(tab[sashell->compt.position]) == 1))
	{
		sashell->compt.position++;
		sashell->red[sashell->has.red] = ft_strjoin(sashell->red[sashell->has.red], " ");
		sashell->red[sashell->has.red] = ft_strjoin(sashell->red[sashell->has.red], tab[sashell->compt.position]);
	}
	else
	{
		sashell->red[sashell->has.red] = ft_strjoin(sashell->red[sashell->has.red], " ");
		sashell->red[sashell->has.red] = ft_strjoin(sashell->red[sashell->has.red], tab[sashell->compt.position] + i);
	}
	return (sashell);
}

t_sashell	*rederiction_parse(t_sashell *sashell, char **tab)
{
	if (tab[sashell->compt.position][0] == '>' && tab[sashell->compt.position][1] != '>')
	{
		sashell->red[sashell->has.red] = ft_strdup("1>");
		sashell = check_file(sashell, tab, 1);
	}
	else if (tab[sashell->compt.position][0] == '<' && tab[sashell->compt.position][1] != '<')
	{
		sashell->red[sashell->has.red] = ft_strdup("1<");
		sashell = check_file(sashell, tab, 1);
	}
	if (tab[sashell->compt.position][0] == '>' && tab[sashell->compt.position][1] == '>')
	{
		sashell->red[sashell->has.red] = ft_strdup("2>");
		sashell = check_file(sashell, tab, 2);
	}
	else if (tab[sashell->compt.position][0] == '<' && tab[sashell->compt.position][1] == '<')
	{
		sashell->red[sashell->has.red] = ft_strdup("2<");
		sashell = check_file(sashell, tab, 2);
	}
	if (sashell->has.red < sashell->compt.red)
		sashell->has.red++;
	return (sashell);
}

t_sashell	*dollar_parse(t_sashell *sashell, char *tab, int i, t_env *env, int compt)
{
	char	*help;
	int		j;
	int		found;

	j = 0;
	found = 0;
	if (compt == 0)
	{
		if (ft_strchr(tab, '$'))
		{

		}
		else
		{
			while (env != NULL)
			{
				if (!ft_strncmp(env->key, tab, ft_strlen(env->key)))
				{
					sashell->tokens[i] = ft_strjoin(sashell->tokens[i], env->value);
					found = 1;
					break ;
				}
				env = env->next;
			}
			sashell->compt.dollar += ft_strlen(tab) + 1;
		}
	}
	return (sashell);
}

t_sashell	*check_dollar(t_sashell *sashell, char **tab, int i, t_env *env)
{
	int		tmp;
	int		quotes;

	sashell->compt.dollar = 0;
	tmp = 0;
	sashell->tokens[i] = ft_strdup("");
	while (tab[sashell->compt.position][sashell->compt.dollar] != '\0')
	{
		if (tab[sashell->compt.position][sashell->compt.dollar] != '$')
			sashell->compt.dollar++;
		else
		{
			if (sashell->compt.dollar > 0 && (tab[sashell->compt.position][sashell->compt.dollar - 1] == '\''
				|| tab[sashell->compt.position][sashell->compt.dollar - 1] == '"'))
			{
				if (tab[sashell->compt.position][sashell->compt.dollar - 1] == '\'')
				{
					// TODO :
				} 
				else
				{
					// TODO :
				}
			}
			else
			{
				sashell->tokens[i] = ft_strjoin(sashell->tokens[i],
					ft_substr(tab[sashell->compt.position], tmp, sashell->compt.dollar - tmp));
				sashell = dollar_parse(sashell, tab[sashell->compt.position] + sashell->compt.dollar + 1, i, env, 0);
			}
		}
	}
	return (sashell);
}

t_sashell	*arg_parse(t_sashell *sashell, char **tab, int i, t_env *env)
{
	while (tab[sashell->compt.position] != '\0' && tab[sashell->compt.position][0] != '>'
		&& tab[sashell->compt.position][0] != '<')
	{
		if (ft_strchr(tab[sashell->compt.position], '$'))
			sashell = check_dollar(sashell, tab, i, env);
		else
			sashell->tokens[i] = ft_strdup(tab[sashell->compt.position]);
		i++;
		sashell->compt.position++;
	}
	sashell->tokens[i] = 0;
	sashell->compt.position--;
	return (sashell);
}

t_sashell	*command_parse(t_sashell *sashell, char **tab, t_env *env)
{
	int		i;
	
	i = 1;
	sashell->tokens[0] = ft_strdup(tab[sashell->compt.position]);
	if (tab[sashell->compt.position + 1])
	{
		sashell->compt.position++;
		if (tab[sashell->compt.position][0] == '-')
		{
			while (tab[sashell->compt.position] && tab[sashell->compt.position][0] == '-')
			{
				sashell->tokens[i] = ft_strdup(tab[sashell->compt.position]);
				i++;
				sashell->compt.position++;
			}
			sashell = arg_parse(sashell, tab, i, env);
		}
		else
			sashell = arg_parse(sashell, tab, i, env);
	}
	else
		sashell->tokens[1] = 0;
	return (sashell);
}

t_sashell	*count_every(t_sashell *sashell, char **tab)
{
	int		i;
	int		quotes;
	int		compt_options;
	int		compt_arg;

	quotes = 0;
	compt_arg = -1;
	compt_options = 0;
	i = 0;
	while (tab[i] != '\0')
	{
		if (tab[i][0] == '"' || tab[i][0] == '\'')
		{
			if (quotes == 0)
				quotes++;
		}
		if ((tab[i][0] == '>' || tab[i][0] == '<') && quotes == 0)
		{
			if (ft_strlen(tab[i]) <= 2 && (ft_strlen(tab[i]) == 1
				|| tab[i][1] == '>' || tab[i][1] == '<'))
				i++;
			sashell->compt.red++;
		}
		else if (tab[i][0] == '-' && i >= 1 && tab[i - 1][0] && quotes == 0)
			compt_options++;
		else
		{
			if (quotes == 1)
				quotes--;
			compt_arg++;
		}
		i++;
	}
	sashell->red = (char **)malloc((sizeof(char *)) * (sashell->compt.red + 1));
	sashell->tokens = (char **)malloc((sizeof(char *)) * (compt_options + compt_arg + 1 + 1));
	return (sashell);
}

t_sashell	*initialize(t_sashell *sashell)
{
	sashell->compt.red = 0;
	sashell->has.red = 0;
	sashell->has.option = 0;
	sashell->has.arg = 0;
	sashell->compt.tokens = 0;
	sashell->compt.position = 0;
	sashell->red = NULL;
	sashell->tokens = NULL;
	return (sashell);
}

t_sashell	*fill_in_the_blank(t_sashell *sashell, char *tab, t_env *env)
{
	char	**help;
	int	i = 0;

	sashell = initialize(sashell);
	help = split_pipe(tab, ' ');
	sashell =  count_every(sashell, help);
	while (help[sashell->compt.position])
	{
		if (help[sashell->compt.position][0] == '<' || help[sashell->compt.position][0] == '>')
			sashell = rederiction_parse(sashell, help);
		else if (ft_isalpha(help[sashell->compt.position][0]))
			sashell = command_parse(sashell, help, env);
		else
		{
			printf("SASHELL: %s: command not found\n", help[0]);
			break ;
		}
		sashell->compt.position++;
	}
	sashell->red[sashell->has.red] = 0;
	while (sashell->tokens[i] != '\0')
	{
		//if (i == 0)
			//printf("command = %s\n", sashell->tokens[i++]);
	//	if (sashell->tokens[i] != '\0')
	//		printf("arg %s\n", sashell->tokens[i]);
	//	else
	//		break;
		i++;
	}
	i = 0;
	while (sashell->red[i] != '\0')
	{
		//printf("red = %s\n", sashell->red[i]);
		i++;
	}
	
	return (sashell);
}

t_sashell	*parse_time(char **tab, t_env *env)
{
	t_sashell	*sashell;
	t_sashell	*tmp;
	int	i;

	if (!tab[0])
		return (NULL);
	sashell = (t_sashell *)malloc(sizeof(t_sashell));
	tmp = (t_sashell *)malloc(sizeof(t_sashell));
	i = 1;
	if (!sashell)
		return (NULL);
	tmp = fill_in_the_blank(sashell, tab[0], env);
	while (tab[i])
	{
		sashell = fill_in_the_blank(sashell, tab[i], env);
		if (tab[i + 1])
		{
			sashell->next = (t_sashell *)malloc(sizeof(t_sashell));
			if (!sashell->next)
				return (NULL);
			sashell = sashell->next;
		}
		i++;
	}
	return (sashell);
}

char	**delete_spaces(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] == ' ')
			j++;
		tab[i] = ft_strdup(tab[i] + j);
		i++;
	}
	return (tab);
}

t_env	*fill_env(t_env *env, char *envp)
{
	char	**help;

	help = ft_split(envp, '=');
	env->key = ft_strdup(help[0]);
	env->value = ft_strdup(help[1]);
	return (env);
}

t_env	*split_env(t_env *env, char **envp)
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

void print_sashell(t_sashell *sashell)
{
	int i = 0;

	while (sashell->tokens[i] != '\0')
	{
		if (i == 0)
			printf("command = %s\n", sashell->tokens[i++]);
		if (sashell->tokens[i] != '\0')
			printf("arg %s\n", sashell->tokens[i]);
		else
			break;
		i++;
	}
}



void exec_cmd(t_sashell *sashell)
{
	char **cmd;
	int ret;

	cmd = sashell->tokens;

	if (cmd && is_builtin(cmd[0]))
		ret = exec_builtin(cmd);


}

void minishell(t_sashell *sashell)
{
	// fuction to handle error on the sashell structure

	// condition to check if it's a built-in 
	exec_cmd(sashell);




}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**tab;
	t_sashell	*sashell;
	t_env		*env;

	while (1)
	{
		line = readline("SASHELL $");
		add_history(line);
		tab = split_pipe(line, '|');
		tab = delete_spaces(tab);
		env = split_env(env, envp);
		sashell = parse_time(tab, env);

		//print_sashell(sashell);
		
		minishell(sashell);
	}
	return (0);
}
