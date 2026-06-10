#include "minishell.h"

int	ft_unset(t_minishell *ms, char **args, bool child)
{
	if (!args[1])
		return (SUCCESS);
	if (child == false)
	{
		if (!is_valid_key(args[1]))
		{
			printf("unset: `%s': not a valid identifier\n", args[1]);
			return (FAILURE);
		}
		envlst_remove(ms, args[1]);
	}
	return (SUCCESS);
}
