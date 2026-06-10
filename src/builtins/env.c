#include "minishell.h"

int	ft_env(t_minishell *ms)
{
	t_env	*lst;

	lst = ms->envlst;
	if (!lst)
	{
		printf("env: no env\n");
		return (FAILURE);
	}
	while (lst)
	{
		if (lst->value != NULL && lst->has_equal)
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return (SUCCESS);
}
