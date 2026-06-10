#include "minishell.h"

static int	init_env_values(char *value, t_env *envlst, char *key)
{
	char	*raw;

	if (value)
	{
		free(envlst->value);
		envlst->value = ft_strdup(value);
	}
	free(envlst->raw);
	raw = ft_strjoin(key, "=");
	if (!raw)
		return (FAILURE);
	envlst->has_equal = true;
	envlst->raw = ft_strjoin(raw, value);
	free(raw);
	if (!envlst->raw)
		return (FAILURE);
	return (SUCCESS);
}

int	envlst_update(t_minishell *ms, char *key, char *value, bool create)
{
	t_env	*envlst;

	envlst = ms->envlst;
	while (envlst)
	{
		if (ft_strcmp(key, envlst->key) == 0)
			return (init_env_values(value, envlst, key));
		envlst = envlst->next;
	}
	if (create)
		return (create_node(ms, key, value, true));
	return (FAILURE);
}

int	envlst_update_without_equal(t_minishell *ms, char *key, bool create)
{
	t_env	*envlst;

	envlst = ms->envlst;
	while (envlst)
	{
		if (ft_strcmp(key, envlst->key) == 0)
		{
			return (SUCCESS);
		}
		envlst = envlst->next;
	}
	if (create)
		return (create_node(ms, key, NULL, false));
	return (FAILURE);
}
