#include "minishell.h"

bool	envlst_key_exists(t_minishell *ms, char *key)
{
	t_env	*envlst;

	envlst = ms->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (true);
		envlst = envlst->next;
	}
	return (false);
}

char	*envlst_get_value(t_minishell *ms, char *key)
{
	t_env	*envlst;

	envlst = ms->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

t_env	*envlst_get_env(t_minishell *ms, char *key)
{
	t_env	*envlst;

	envlst = ms->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst);
		envlst = envlst->next;
	}
	return (NULL);
}
