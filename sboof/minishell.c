/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:10:34 by amaach            #+#    #+#             */
/*   Updated: 2021/10/05 18:05:22 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	sashell->compt.position++;
	return (sashell);
}

t_sashell	*dollar_parse(t_sashell *sashell, char *tab, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, tab, ft_strlen(tab)) == 0
			&& ft_strncmp(env->key, tab, ft_strlen(env->key)) == 0)
		{
			sashell->tokens[sashell->compt.tokens] = ft_strjoin(sashell->tokens[sashell->compt.tokens], env->value);
			break ;
		}
		env = env->next;
	}
	sashell->compt.dollar++;
	return (sashell);
}

t_sashell	*check_dollar(t_sashell *sashell, char *tab, t_env *env)
{
	int		compt;
	int		compt_help;
	char	*help;

	compt = 0;
	if (sashell->compt.dollar == 0)
		sashell->tokens[sashell->compt.tokens] = ft_strdup("");
	while (ft_isalnum(tab[compt]))
		compt++;
	sashell->tokens[sashell->compt.tokens] = ft_strjoin(sashell->tokens[sashell->compt.tokens],
		ft_substr(tab, 0, compt));
	if (tab[compt] == '$')
	{
		compt++;
		if (tab[compt] == '"')
		{
			
		}
		else if (tab[compt] == '\'')
		{

		}
		else
		{
			compt_help = compt;
			while (ft_isalnum(tab[compt_help]))
				compt_help++;
			help = ft_substr(tab, compt, compt_help - 1);
			sashell = dollar_parse(sashell, help, env);
			free(help);
			if (ft_strchr(tab + compt_help, '$'))
				sashell = check_dollar(sashell, tab + compt_help, env);
		}
	}
	else if (tab[compt] == '"')
	{
		
	}
	else if (tab[compt] == '\'')
	{
		
	}
	return (sashell);
}

t_sashell	*arg_parse(t_sashell *sashell, char **tab, t_env *env)
{
	while (tab[sashell->compt.position] != '\0' && tab[sashell->compt.position][0] != '>'
		&& tab[sashell->compt.position][0] != '<')
	{
		if (ft_strchr(tab[sashell->compt.position], '$'))
			sashell = check_dollar(sashell, tab[sashell->compt.position], env);
		else
			sashell->tokens[sashell->compt.tokens] = ft_strdup(tab[sashell->compt.position]);
		sashell->compt.tokens++;
		sashell->compt.position++;
	}
	sashell->tokens[sashell->compt.tokens] = 0;
	return (sashell);
}

t_sashell	*command_parse(t_sashell *sashell, char **tab, t_env *env)
{
	sashell->tokens[sashell->compt.tokens++] = ft_strdup(tab[sashell->compt.position++]);
	if (tab[sashell->compt.position])
	{
		if (tab[sashell->compt.position][0] == '-')
		{
			while (tab[sashell->compt.position] && tab[sashell->compt.position][0] == '-')
			{
				sashell->tokens[sashell->compt.tokens] = ft_strdup(tab[sashell->compt.position]);
				sashell->compt.tokens++;
				sashell->compt.position++;
			}
			sashell = arg_parse(sashell, tab, env);
		}
		else
			sashell = arg_parse(sashell, tab, env);
	}
	else
		sashell->tokens[sashell->compt.tokens] = 0;
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
	sashell->compt.dollar = 0;
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
		else if (ft_isalpha(help[sashell->compt.position][0]) || sashell->compt.tokens > 0)
			sashell = command_parse(sashell, help, env);
		else
		{
			printf("SASHELL: %s: command not found\n", help[0]);
			break ;
		}
	}
	sashell->red[sashell->has.red] = 0;
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
	i = 1;
	if (!sashell)
		return (NULL);
	sashell = fill_in_the_blank(sashell, tab[0], env);
	tmp = sashell;
	sashell->next = (t_sashell *)malloc(sizeof(t_sashell));
	if (!sashell->next)
		return (NULL);
	if (!tab[i])
	{
		sashell->next = NULL;
		return (sashell);
	}
	sashell = sashell->next;
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
	sashell->next = NULL;
	sashell = tmp;
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

t_sashell	*parse_function(t_sashell *sashell, t_env *env, char *line)
{
	char	**tab;

	tab = split_pipe(line, '|');
	tab = delete_spaces(tab);
	sashell = parse_time(tab, env);
	return (sashell);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*line;
	
// 	t_sashell	*sashell;
// 	t_env		*env;
// 	t_sashell	*tmp;
// 	int		i;
// 	int		compt;

// 	while (1)
// 	{
// 		line = readline("SASHELL $");
// 		add_history(line);
// 		env = split_env(env, envp);
// 		sashell = parse_function(sashell, env, line);
// 		// tmp = sashell;
// 		// compt = 1;
// 		// while (sashell)
// 		// {
// 		// 	i = -1;
// 		// 	printf("*********************************\n");
// 		// 	while (sashell->tokens[++i])
// 		// 		printf("pipe[%d]...tokens[%d] = %s\n", compt, i, sashell->tokens[i]);
// 		// 	i = -1;
// 		// 	while (sashell->red[++i])
// 		// 		printf("pipe[%d]...red[%d] = %s\n", compt, i, sashell->red[i]);
// 		// sashell = sashell->next;
// 		// 	compt++;
// 		// }
// 		// printf("*********************************\n");
// 		// sashell = tmp;
// 	}
// 	return (0);
// }
