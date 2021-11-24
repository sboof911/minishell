
#include "../minishell.h"
int g_env = 0;

int		tab_len(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i] != NULL)
			i++;
	}
	return (i);
}

char	*is_special(char c)
{
	return (ft_strchr("$\\\"", c));
}

t_env	*new_env(char *key, char *value)
{
	t_env *new;

	if (!(new = (t_env *)malloc(sizeof(t_env))))
		return (0);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}


int		string_equal(char *s1, char *s2)
{
	int res;

	res = strncmp(s1, s2, max_v(ft_strlen(s1), ft_strlen(s2)));
	return (res == 0);
}

int			max_v(int a, int b)
{
	return ((a > b ? a : b));
}

int			min_v(int a, int b)
{
	return ((a < b ? a : b));
}
