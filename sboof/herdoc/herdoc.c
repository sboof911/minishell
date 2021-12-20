/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaach <amaach@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:37:32 by amaach            #+#    #+#             */
/*   Updated: 2021/12/20 10:32:49 by amaach           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	quit_handler(int num)
{
	char	cwd[PATH_MAX];

	if (num == SIGQUIT)
		return ;
	ft_putchar('\n');
	rl_on_new_line();
	getcwd(cwd, PATH_MAX);
	printf("\e[48;5;098m~%s", cwd);
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quit_handlerherdoc(int num)
{
	if (num == SIGQUIT)
		return ;
	ft_putchar('\n');
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*heredoc(t_sashell *sashell, int i)
{
	int		fd;
	char	*line;
	char	*random_string;

	random_string = generate_random_value();
	fd = open(random_string, O_CREAT | O_RDWR, S_IRWXU);
	// signal(SIGQUIT, &quit_handlerherdoc);
	// signal(SIGINT, &quit_handlerherdoc);
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
	close(fd);
	return (NULL);
}

t_sashell	*red_open(t_sashell *sashell)
{
	int			i;
	char		*tmp;
	t_sashell	*help;

	help = sashell;
	while (sashell)
	{
		i = 0;
		while (sashell->red[i] != 0)
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
		sashell = sashell->next;
	}
	sashell = help;
	return (sashell);
}
