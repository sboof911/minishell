/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 12:10:34 by amaach            #+#    #+#             */
/*   Updated: 2021/11/16 21:39:30 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_sashell	*check_file(t_sashell *sashell, char *tab, int i)
{
	if (tab[0] != '>' && tab[0] != '<')
		i = 0;
	sashell->red[sashell->has.red]
		= ft_strjoin(sashell->red[sashell->has.red], " ");
	sashell->red[sashell->has.red]
		= ft_strjoin(sashell->red[sashell->has.red], tab + i);
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
	sashell->has.red++;
	return (sashell);
}

char	rederiction_sign(char *tab)
{
	char	red;

	red = 0;
	if (ft_strlen(tab) == 1
		|| (ft_strlen(tab) == 2 && (tab[1] == '<' || tab[1] == '>')))
	{
		if (ft_strlen(tab) == 1)
		{
			if (tab[0] == '<')
				red = '<';
			else
				red = '>';
		}
		else
		{
			if (tab[0] == '<')
				red = '4';
			else
				red = '7';
		}
	}
	return (red);
}

int	help_rederiction(t_sashell *sashell, char **tab, int i)
{
	while (tab[sashell->compt.position][i] == '>'
		|| tab[sashell->compt.position][i] == '<')
		i++;
	while (tab[sashell->compt.position][i] != '<'
		&& tab[sashell->compt.position][i] != '>'
		&& tab[sashell->compt.position][i] != '\0')
		i++;
	return (i);
}

int	help_red(char **tab, int i, t_sashell *sashell, int remember)
{
	if (tab[sashell->compt.position][i] != '\0')
		remember = i;
	return (remember);
}

t_sashell	*parse_red(t_sashell *sashell, char **tab, int i, int remember)
{
	char	*help;
	char	red;

	while (tab[sashell->compt.position][i] != '\0')
	{
		red = rederiction_sign(tab[sashell->compt.position]);
		sashell->compt.position += (red != 0);
		i = help_rederiction(sashell, tab, i);
		help = ft_substr(tab[sashell->compt.position], remember, i - remember);
		if (!red)
		{
			red = rederiction_sign(help);
			if (red)
			{
				free(help);
				sashell->compt.position++;
				i = help_rederiction(sashell, tab, 0);
				help = ft_substr(tab[sashell->compt.position], 0, i);
			}
		}
		sashell = rederiction_parse(sashell, help, red);
		free(help);
		remember = help_red(tab, i, sashell, remember);
	}
	return (sashell);
}

t_sashell	*dollar_parse(t_sashell *sashell, char *tab, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->key, tab, ft_strlen(tab)) == 0
			&& ft_strncmp(env->key, tab, ft_strlen(env->key)) == 0)
		{
			sashell->tokens[sashell->compt.tokens]
				= ft_strjoin(sashell->tokens[sashell->compt.tokens],
					env->value);
			break ;
		}
		env = env->next;
	}
	sashell->compt.dollar++;
	return (sashell);
}

int	help_check_dollar(t_sashell *sashell, char *tab, t_env *env, int i)
{
	int		compt;
	char	*help;

	compt = 0;
	if (tab[i] != '\0')
	{
		compt = i;
		while (ft_isalnum(tab[i]))
			i++;
		if (compt == i && tab[i] != '\'')
			sashell->tokens[sashell->compt.tokens]
				= ft_charjoin(sashell->tokens[sashell->compt.tokens], '$');
		else
		{
			help = ft_substr(tab, compt, i - compt);
			i--;
			sashell = dollar_parse(sashell, help, env);
			free(help);
		}
	}
	return (i);
}

int	help_dollar_quotes(int d_q)
{
	if (d_q == 0)
		d_q = 1;
	else
		d_q = 0;
	return (d_q);
}

t_sashell	*help_norm_dollar(t_sashell *sashell, char *tab, int i)
{
	if (tab[i] == '\0')
	{
		sashell->tokens[sashell->compt.tokens]
			= ft_charjoin(sashell->tokens[sashell->compt.tokens], '$');
	}
	return (sashell);
}

int	some_shit(int *d_quotes, int *s_quotes, char *tab, int i)
{
	if (tab[i] == '"' && *s_quotes == 0)
	{
		*d_quotes = help_dollar_quotes(*d_quotes);
		return (1);
	}
	else if (tab[i] == '\'' && *d_quotes == 0)
	{
		*s_quotes = help_dollar_quotes(*s_quotes);
		return (1);
	}
	return (0);
}

t_sashell	*check_dollar(t_sashell *sashell, char *tab, t_env *env, int i)
{
	int		d_quotes;
	int		s_quotes;

	d_quotes = 0;
	s_quotes = 0;
	sashell->tokens[sashell->compt.tokens] = ft_strdup("");
	while (tab[++i] != '\0')
	{
		if (some_shit(&d_quotes, &s_quotes, tab, i))
			continue ;
		else if (tab[i] == '$' && s_quotes == 0)
		{
			i = help_check_dollar(sashell, tab, env, i + 1);
			if (tab[i] == '\0')
			{
				sashell->tokens[sashell->compt.tokens]
					= ft_charjoin(sashell->tokens[sashell->compt.tokens], '$');
				return (sashell);
			}
		}
		else
			sashell->tokens[sashell->compt.tokens]
				= ft_charjoin(sashell->tokens[sashell->compt.tokens], tab[i]);
	}
	return (sashell);
}

int	count_quotes(char *tab)
{
	int		i;
	int		compt1;
	int		compt2;

	i = 0;
	compt1 = 0;
	compt2 = 0;
	while (tab[i] != '\0')
	{
		if (tab[i] == '"')
			compt1++;
		if (tab[i] == '\'')
			compt2++;
		i++;
	}
	if (compt1 % 2 == 1 || compt2 % 2 == 1)
		ft_putstr("quotes non fermer");
	return (compt1 + compt2);
}

char	*delete_quotes(char *tab)
{
	int		i;
	int		compt;
	int		j;
	char	*str;

	j = -1;
	compt = 0;
	compt = count_quotes(tab);
	str = (char *)malloc(ft_strlen(tab) - compt + 1);
	i = -1;
	while (tab[++i] != '\0')
	{
		if (tab[i] != '"' && tab[i] != '\'')
			str[++j] = tab[i];
	}
	str[++j] = '\0';
	free(tab);
	return (str);
}

t_sashell	*arg_parse(t_sashell *sashell, char **tab, t_env *env)
{
	while (tab[sashell->compt.position] != '\0'
		&& tab[sashell->compt.position][0] != '>'
		&& tab[sashell->compt.position][0] != '<')
	{
		if (ft_strchr(tab[sashell->compt.position], '$'))
			sashell = check_dollar(sashell, tab[sashell->compt.position],
					env, -1);
		else
		{
			sashell->tokens[sashell->compt.tokens]
				= ft_strdup(tab[sashell->compt.position]);
			sashell->tokens[sashell->compt.tokens]
				= delete_quotes(sashell->tokens[sashell->compt.tokens]);
		}
		sashell->compt.tokens++;
		sashell->compt.position++;
	}
	sashell->tokens[sashell->compt.tokens] = 0;
	return (sashell);
}

t_sashell	*command_parse(t_sashell *sashell, char **tab, t_env *env)
{
	sashell->tokens[sashell->compt.tokens++]
		= ft_strdup(tab[sashell->compt.position++]);
	if (tab[sashell->compt.position])
	{
		if (tab[sashell->compt.position][0] == '-')
		{
			while (tab[sashell->compt.position]
				&& tab[sashell->compt.position][0] == '-')
			{
				sashell->tokens[sashell->compt.tokens]
					= ft_strdup(tab[sashell->compt.position]);
				sashell->compt.tokens++;
				sashell->compt.position++;
			}
			sashell = arg_parse(sashell, tab, env);
		}
		else
			sashell = arg_parse(sashell, tab, env);
	}
	return (sashell);
}

t_sashell	*count_every(t_sashell *sashell, char *tab)
{
	sashell->red = (char **)malloc((sizeof(char *)) * (1024));
	sashell->tokens = (char **)malloc((sizeof(char *)) * (1024));
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

	sashell = initialize(sashell);
	help = split_pipe(tab, ' ');
	sashell = count_every(sashell, tab);
	while (help[sashell->compt.position])
	{
		if (help[sashell->compt.position][0] == '<'
			|| help[sashell->compt.position][0] == '>')
		{
			sashell = parse_red(sashell, help, 0, 0);
			sashell->compt.position++;
		}
		else if (ft_isalpha(help[sashell->compt.position][0])
			|| sashell->compt.tokens > 0)
			sashell = command_parse(sashell, help, env);
	}
	sashell->tokens[sashell->compt.tokens] = 0;
	sashell->red[sashell->has.red] = 0;
	ft_free(help, sashell->compt.position);
	return (sashell);
}

t_sashell	*next_sashell(t_sashell *sashell, t_env *env, char **tab)
{
	int		i;

	i = 1;
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
	return (sashell);
}

t_sashell	*parse_time(char **tab, t_env *env)
{
	t_sashell	*sashell;
	t_sashell	*tmp;

	if (!tab[0])
		return (NULL);
	sashell = (t_sashell *)malloc(sizeof(t_sashell));
	if (!sashell)
		return (NULL);
	sashell = fill_in_the_blank(sashell, tab[0], env);
	tmp = sashell;
	sashell->next = (t_sashell *)malloc(sizeof(t_sashell));
	if (!sashell->next)
		return (NULL);
	if (!tab[1])
	{
		free(sashell->next);
		sashell->next = NULL;
		return (sashell);
	}
	sashell = next_sashell(sashell, env, tab);
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
	tmp = (char **)malloc(sizeof(char *) * (ft_count_tab(tab) + 1));
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

int	ft_count_tab(char **tab)
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

int	check_red(char *line, int i)
{
	int	compt1;
	int	compt2;
	int	red1;
	int	red2;

	red1 = 0;
	red2 = 0;
	compt1 = 0;
	compt2 = 0;
	while (line[++i] != '\0')
	{
		compt1 += (line[i] == '"');
		compt2 += (line[i] == '\'');
		red1 += (line[i] == '<' && compt1 % 2 == 0 && compt2 % 2 == 0);
		red2 += (line[i] == '>' && compt1 % 2 == 0 && compt2 % 2 == 0);
		if (red1 > 0 && red2 > 0)
			return (0);
		if (ft_isalnum(line[i]) && red1 < 3)
			red1 = 0;
		if (ft_isalnum(line[i]) && red2 < 3)
			red2 = 0;
	}
	if (red1 > 0 || red2 > 0)
		return (0);
	return (1);
}

int	check_quotes(char *line)
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

int	help_check_pipe(char *line, int i, int compt1, int compt2)
{
	if (line[i - 1] == '|' && compt1 % 2 == 0 && compt2 % 2 == 0)
	{
		while (line[i] != '\0' && line[i] == ' ')
			i++;
		if (line[i] != '>' && line[i] != '<')
		{
			if (!ft_isalnum(line[i]))
				return (-1);
		}
	}
	return (i);
}

int	check_pipe(char *line, int i, int pipe, int compt1)
{
	int		compt2;

	compt2 = 0;
	while (line[i] != '\0')
	{
		if (i > 0)
		{
			i = help_check_pipe(line, i, compt1, compt2);
			if (i == -1)
				return (0);
		}
		compt1 += (line[i] == '"');
		compt2 += (line[i] == '\'');
		pipe += (line[i] == '|' && compt1 % 2 == 0 && compt2 % 2 == 0);
		if (ft_isalnum(line[i]) && pipe < 2)
			pipe = 0;
		i++;
	}
	if (pipe > 0)
		return (0);
	return (1);
}

int	help_check_sytax(char *line, int i)
{
	if (check_quotes(line) != 1)
	{
		ft_putstr("SASHELL : Syntax Error // quotes not closed\n");
		return (0);
	}
	if (check_red(line, i - 1) != 1)
	{
		ft_putstr("SASHELL : Syntax Error // redirections\n");
		return (0);
	}
	return (1);
}

int	check_sytaxerr(char *line)
{
	int		i;
	int		pipe;
	int		compt1;
	int		compt2;

	compt1 = 0;
	compt2 = 0;
	pipe = 0;
	i = 0;
	if (!help_check_sytax(line, 0))
		return (0);
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if ((line[i] != '>' && line[i] != '<') && (!ft_isalnum(line[i])))
	{
		ft_putstr("SASHELL : Syntax Error\n");
		return (0);
	}
	if (check_pipe(line, i, 0, 0) != 1)
	{
		ft_putstr("SASHELL : Syntax Error // pipe\n");
		return (0);
	}
	return (1);
}

char	*generate_random_value(void)
{
	int				fd;
	unsigned int	randval;
	char			*rand_string;
	char			*r_string;
	char			*tmp;

	fd = open("/dev/random", O_RDONLY);
	read(fd, &randval, sizeof(randval));
	close(fd);
	rand_string = ft_itoa(randval);
	tmp = ft_strdup("/tmp/heredoc-");
	r_string = ft_strjoin(tmp, rand_string);
	free (rand_string);
	return (r_string);
}

char	*heredoc(t_sashell *sashell, int i)
{
	int		fd;
	char	*line;
	char	*random_string;

	random_string = generate_random_value();
	fd = open(random_string, O_CREAT | O_RDWR, S_IRWXU);
	while (420)
	{	
		line = readline("> ");
		if (!line || !ft_strncmp(line, sashell->red[i] + 3,
				ft_strlen(sashell->red[i] + 3)))
		{
			if (line)
				free(line);
			close(fd);
			return (random_string);
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
	return (NULL);
}

t_sashell	*red_open(t_sashell *sashell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (sashell->red[i] != '\0')
	{
		if (sashell->red[i][0] == '2' && sashell->red[i][1] == '<')
		{
			tmp = heredoc(sashell, i);
			free(sashell->red[i]);
			sashell->red[i] = ft_strdup("1< ");
			sashell->red[i] = ft_strjoin(sashell->red[i], tmp);
			free(tmp);
		}
		i++;
	}
	return (sashell);
}

t_sashell	*parse_function(t_sashell *sashell, t_env *env, char *line)
{
	char	**tab;

	if (check_sytaxerr(line) == 1)
	{
		tab = split_pipe(line, '|');
		tab = delete_spaces(tab);
		sashell = parse_time(tab, env);
		ft_free(tab, ft_count_tab(tab));
		red_open(sashell);
		free(line);
		return (sashell);
	}
	return (NULL);
}
