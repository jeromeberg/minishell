#include "minishell.h"

bool	is_valid_key(char *key)
{
	int	i;

	i = 1;
	if (!key)
		return (false);
	if (!(isalpha(key[0]) || key[0] == '_'))
		return (false);
	while (key[i])
	{
		if (!(isalnum(key[i]) || key[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

void	free_env(t_env *envlst)
{
	t_env	*tmp;

	while (envlst)
	{
		tmp = envlst;
		envlst = envlst->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		if (tmp->raw)
			free(tmp->raw);
		free(tmp);
	}
	envlst = NULL;
}
