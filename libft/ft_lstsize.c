#include "libft.h"

/**
 * @brief Count the nb of nodes in a list.
 * @param lst Beginning of the list.
 * @return Nb of nodes.
 */
int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*current;

	i = 0;
	current = lst;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	return (i);
}
