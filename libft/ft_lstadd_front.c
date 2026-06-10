#include "libft.h"

/**
 * @brief Add a node at the beginning of the list.
 * @param lst Address of a ptr to the first node.
 * @param new Node to add.
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
}
