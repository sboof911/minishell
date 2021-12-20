/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:35:20 by amaach            #+#    #+#             */
/*   Updated: 2021/12/20 22:26:34 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	check_quotes(char *line, int i)
{
	int	compt1;
	int	compt2;

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
			if (line[i] == '|')
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
		if (line[i] != '|' && pipe < 2)
			pipe = 0;
		i++;
	}
	if (pipe > 0)
		return (0);
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
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (!help_check_sytax(line, i))
		return (0);
	if (check_pipe(line, i, 0, 0) != 1)
	{
		g_.exit_value = 127;
		ft_putstr("SASHELL : Syntax error\n");
		return (0);
	}
	return (1);
}
