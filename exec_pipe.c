#include "minishell.h"


char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		size_s1;

	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *s1) && *s1 != '\0')
		s1++;
	size_s1 = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[size_s1]) && size_s1 != 0)
		size_s1--;
	return (ft_substr((char *)s1, 0, size_s1 + 1));
}


int		has_quote(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
	}
	return (0);
}

int		has_env(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			return (1);
	}
	return (0);
}

char	*modify_argv(char *str, t_env *envs)
{
	char	*ret;

	ret = 0;
	if (has_quote(str))
		ret = parse_quote(str, envs);
	else if (has_env(str))
		ret = parse_env(str, envs);
	free(str);
	return (ret);
}

char	**get_argv(char *line, t_env *envs)
{
	int		i;
	char	**argv;

	if (!(argv = ft_split(line, ' ')))
		return (0);
	i = -1;
	while (argv[++i])
	{
		if ((ft_strlen(argv[i]) != 1)
			&& (has_quote(argv[i]) || has_env(argv[i])))
			argv[i] = modify_argv(argv[i], envs);
	}
	return (argv);
}

void	parse_pipe(char **line, t_pipe *p, t_env *envs)
{
	int		i;
	char	*temp;
	char	*temp2;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '|')
		{
			temp = ft_substr(*line, 0, i);
			p->line = ft_strtrim(temp, " ");
			free(temp);
			temp = ft_substr(*line, i + 1, ft_strlen(*line) - i);
			temp2 = ft_strtrim(temp, " ");
			free(temp);
			*line = temp2;
			p->argv = get_argv(p->line, envs);
			return ;
		}
	}
}

void	exec_pipe_case_zero(int child, int fd[2], t_env *envs, t_pipe p, char *line, t_sashell *sashell)
{
	if (child == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
        minishell(sashell, envs, line);
		exec_cmd(p.line, envs);
		exit(EXIT_SUCCESS);
	}
}

void	exec_pipe_case_one(int child, int fd[2], t_env *envs, char *line, t_sashell *sashell)
{
	if (child == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
        minishell(sashell, envs, line);
		exec_cmd(line, envs);
		exit(EXIT_SUCCESS);
	}
}

void	exec_pipe(char *line, t_env *envs, t_sashell *sashell)
{
	int		fd[2];
	int		child[2];
	int		status[2];
	t_pipe	p;

	parse_pipe(&line, &p, envs);
	pipe(fd);
	child[0] = fork();
	exec_pipe_case_zero(child[0], fd, envs, p, line, sashell);
	free_double_arr(p.argv);
	free(p.line);
	child[1] = fork();
	exec_pipe_case_one(child[1], fd, envs, line, sashell);
	free(line);
	close(fd[0]);
	close(fd[1]);
	waitpid(child[1], &status[1], 0);
	waitpid(child[0], &status[0], WNOHANG);
}
