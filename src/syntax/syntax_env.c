#include "minishell.h"

char	*get_env_value(t_env *env, char *token)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, token) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

bool	is_env_dir(char *token, t_env *env)
{
	char	*value;

	if (!token || token[0] != '$')
		return (false);
	value = get_env_value(env, token + 1);
	if (!value || !*value)
		return (false);
	return (is_directory(value));
}
