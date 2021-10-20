/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:10:34 by amaach            #+#    #+#             */
/*   Updated: 2021/10/20 18:00:25 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_sashell	*check_file(t_sashell *sashell, char *tab, int i)
{
	if (tab[0] != '>' && tab[0] != '<')
		i = 0;
	sashell->red[sashell->has.red] = ft_strjoin(sashell->red[sashell->has.red], " ");
	sashell->red[sashell->has.red] = ft_strjoin(sashell->red[sashell->has.red], tab + i);
	return (sashell);
}

t_sashell	*rederiction_parse(t_sashell *sashell, char *tab, char red)
{
	if ((tab[0] == '>' && tab[1] != '>') || red == '>')
	{
		sashell->red[sashell->has.red] = ft_strdup("1>");
		sashell = check_file(sashell, tab, 1);
	}
	else if ((tab[0] == '<' && tab[1] != '<') || red == '<')
	{
		sashell->red[sashell->has.red] = ft_strdup("1<");
		sashell = check_file(sashell, tab, 1);
	}
	if ((tab[0] == '>' && tab[1] == '>') || red == '7')
	{
		sashell->red[sashell->has.red] = ft_strdup("2>");
		sashell = check_file(sashell, tab, 2);
	}
	else if ((tab[0] == '<' && tab[1] == '<') || red == '4')
	{
		sashell->red[sashell->has.red] = ft_strdup("2<");
		sashell = check_file(sashell, tab, 2);
	}
	if (sashell->has.red < sashell->compt.red)
		sashell->has.red++;
	return (sashell);
}

t_sashell	*parse_rederiction(t_sashell *sashell, char **tab)
{
	char	*help;
	int		i;
	int		remember;
	char	red;

	red = 0;
	i = 0;
	remember = 0;
	while (tab[sashell->compt.position][i] != '\0')
	{
		i++;
		if (ft_strlen(tab[sashell->compt.position]) == 1 ||
			(ft_strlen(tab[sashell->compt.position]) == 2 && (tab[sashell->compt.position][1] == '<'
			|| tab[sashell->compt.position][1] == '>')))
		{
			if (ft_strlen(tab[sashell->compt.position]) == 1)
			{
				if (tab[sashell->compt.position][0] == '<')
					red = '<';
				else
					red = '>';
			}
			else
			{
				if (tab[sashell->compt.position][0] == '<')
					red = '4';
				else
					red = '7';
			}
			i = 0;
			sashell->compt.position++;
		}
		if (tab[sashell->compt.position][i] == '>' || tab[sashell->compt.position][i] == '<')
			i++;
		while (tab[sashell->compt.position][i] != '<' && tab[sashell->compt.position][i] != '>'
				&& tab[sashell->compt.position][i] != '\0')
			i++;
		help = ft_substr(tab[sashell->compt.position], remember, i - remember);
		sashell = rederiction_parse(sashell, help, red);
		free(help);
		if (tab[sashell->compt.position][i] != '\0')
		{
			remember = i;
			i++;
			if (tab[sashell->compt.position][i] == '>' || tab[sashell->compt.position][i] == '<')
				i++;
		}
		red = 0;
	}
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
	int		i;
	int		d_quotes;
	int		s_quotes;
	int		compt;
	char	*help;

	d_quotes = 0;
	s_quotes = 0;
	i = 0;
	sashell->tokens[sashell->compt.tokens] = ft_strdup("");
	while (tab[i] != '\0')
	{
		if (tab[i] == '"' && s_quotes == 0)
		{
			if (d_quotes == 0)
				d_quotes = 1;
			else
				d_quotes = 0;
		}
		else if (tab[i] == '\'' && d_quotes == 0)
		{
			if (s_quotes == 0)
				s_quotes = 1;
			else
				s_quotes = 0;
		}
		else if (tab[i] == '$' && s_quotes == 0)
		{
			i++;
			if (tab[i] != '\0')
			{
				compt = i;
				while (ft_isalnum(tab[i]))
					i++;
				if (compt == i && tab[i] != '\'')
					sashell->tokens[sashell->compt.tokens] = ft_charjoin(sashell->tokens[sashell->compt.tokens], '$');
				else
				{
					help = ft_substr(tab, compt, i - compt);
					i--;
					sashell = dollar_parse(sashell, help, env);
					free(help);
				}
			}
			else
			{
				sashell->tokens[sashell->compt.tokens] = ft_charjoin(sashell->tokens[sashell->compt.tokens], '$');
				return (sashell);
			}
		}
		else
			sashell->tokens[sashell->compt.tokens] = ft_charjoin(sashell->tokens[sashell->compt.tokens], tab[i]);
		i++;
	}
	return (sashell);
}

int		count_quotes(char *tab)
{
	int		i;
	int		compt1;
	int		compt2;

	i = 0;
	compt1 = 0;
	compt2 = 0;
	while (tab[i] != '\0')
	{
		if (tab[i] == '"' && compt2 % 2 != 1)
			compt1++;
		if (tab[i] == '\'' && compt1 % 2 != 1)
			compt2++;
		i++;
	}
	return (compt1 + compt2);
}

char	*delete_quotes(char *tab)
{
	int		i;
	int		compt1;
	int		compt2;
	int		j;
	char	*str;

	j = -1;
	compt1 = 0;
	compt2 = 0;
	str = (char *)malloc(ft_strlen(tab) - count_quotes(tab) + 1);
	i = -1;
	while (tab[++i] != '\0')
	{
		if (tab[i] != '"' && compt1 % 2 == 1)
			str[++j] = tab[i];
		else if (tab[i] != '\'' && compt2 % 2 == 1)
			str[++j] = tab[i];
		if (tab[i] == '"' && compt2 % 2 != 1)
			compt1++;
		else if (tab[i] == '\'' && compt1 % 2 != 1)
			compt2++;
	}
	str[++j] = '\0';
	free(tab);
	return (str);
}

t_sashell	*arg_parse(t_sashell *sashell, char **tab, t_env *env)
{
	while (tab[sashell->compt.position] != '\0' && tab[sashell->compt.position][0] != '>'
		&& tab[sashell->compt.position][0] != '<')
	{
		if (ft_strchr(tab[sashell->compt.position], '$'))
			sashell = check_dollar(sashell, tab[sashell->compt.position], env);
		else
		{
			sashell->tokens[sashell->compt.tokens] = ft_strdup(tab[sashell->compt.position]);
			sashell->tokens[sashell->compt.tokens] = delete_quotes(sashell->tokens[sashell->compt.tokens]);
		}
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
	int		j;

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
		if ((ft_strchr(tab[i], '<') || ft_strchr(tab[i], '>')) && quotes == 0)
		{
			j = 0;
			while (tab[i][j] != '\0')
			{
				if ((tab[i][j] == '>' || tab[i][j] == '<') && (j == 0 || ft_isalnum(tab[i][j - 1])))
					sashell->compt.red++;
				j++;
			}
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
	sashell->error = 0;
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
			sashell = parse_rederiction(sashell, help);
		else
			sashell = command_parse(sashell, help, env);
	}
	ft_free(help, sashell->compt.position);
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
	if (tab[i] == NULL)
	{
		free(sashell->next);
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
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	if (!(tmp = (char **)malloc(sizeof(char *) * (ft_count_tab(tab) + 1))))
		return (NULL);
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] == ' ')
			j++;
		tmp[i] = ft_strdup(tab[i] + j);
		i++;
	}
	tmp[i] = 0;
	ft_free(tab, i);
	return (tmp);
}

int			check_quotes(char *line)
{
	int	i;
	int	compt1;
	int	compt2;

	i = 0;
	compt1 = 0;
	compt2 = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' && compt2 % 2 != 1)
			compt1++;
		if (line[i] == '\'' && compt1 % 2 != 1)
			compt2++;
		i++;
	}
	if ((compt1 % 2 == 1) || (compt2 % 2 == 1))
		return (0);
	return (1);
}

int			check_sytaxerr(char *line)					// check for all errors
{
	int		i;
	int		pipe;
	int		red1;
	int		red2;
	int		compt1;
	int		compt2;

	compt1 = 0;
	compt2 = 0;
	pipe = 0;
	red1 = 0;
	red2 = 0;
	i = 0;
	if (check_quotes(line) != 1)
	{
		ft_putstr("SASHELL : Synatx Error // quotes not closed\n");
		return (0);
	}
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (line[i] != '>' && line[i] != '<')
	{
		if (!ft_isalnum(line[i]))
		{
			ft_putstr("SASHELL : Syntax Error\n");
			return (0);
		}
	}
	while (line[i] != '\0')
	{
		if (i > 0)
		{
			if (line[i - 1] == '|' && compt1 % 2 == 0 && compt2 % 2 == 0)
			{
				while (line[i] != '\0' && line[i] == ' ')
					i++;
				if (line[i] != '>' && line[i] != '<')
				{
					if (!ft_isalnum(line[i]))
					{
						ft_putstr("SASHELL : Syntax Error\n");
						return (0);
					}
				}
			}
		}
		compt1 += (line[i] == '"');
		compt2 += (line[i] == '\'');
		pipe += (line[i] == '|' && compt1 % 2 == 0 && compt2 % 2 == 0);
		if (ft_isalnum(line[i]) && pipe < 2)
			pipe = 0;
		red1 += (line[i] == '<' && compt1 % 2 == 0 && compt2 % 2 == 0);
		red2 += (line[i] == '>' && compt1 % 2 == 0 && compt2 % 2 == 0);
		if (pipe > 0 && (red1 > 0 || red2 > 0))
		{
			ft_putstr("SASHELL : Syntax Error '<> & |'\n");
			return (0);
		}
		if (red1 > 0 && red2 > 0)
		{
			ft_putstr("SASHELL : Syntax Error '<>'\n");
			return (0);
		}
		if (ft_isalnum(line[i]) && red1 < 3)
			red1 = 0;
		if (ft_isalnum(line[i]) && red2 < 3)
			red2 = 0;
		i++;
	}
	if (pipe > 0 || red1 > 0 || red2 > 0)
	{
		ft_putstr("SASHELL : Syntax Error\n");
		return (0);
	}
	return (1);
}

int			ft_count_tab(char **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (tab[i] != NULL)
			i++;
	}
	return (i);
}

t_sashell	*parse_function(t_sashell *sashell, t_env *env, char *line)
{
	char	**tab;

	if (check_sytaxerr(line) == 1)
	{
		tab = split_pipe(line, '|');
		free (line);
		tab = delete_spaces(tab);
		sashell = parse_time(tab, env);
		ft_free(tab, ft_count_tab(tab));
		return (sashell);
	}
	return (NULL);
}
