#include "minishell.h"

int	envlst_len(t_env *src)
{
	t_env	*current;
	int		size;

	current = src;
	size = 0;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}
