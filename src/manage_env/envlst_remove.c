#include "minishell.h"

int	envlst_remove(t_minishell *ms, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = ms->envlst;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				ms->envlst = current->next;
			free(current->key);
			free(current->value);
			free(current->raw);
			free(current);
			return (SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (FAILURE);
}
