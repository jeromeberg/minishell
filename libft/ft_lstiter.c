#include "libft.h"

/**
 * @brief Iterate the list and apply f to each node.
 * @param lst Address of a pointer to a node.
 * @param f Function to apply on each content.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
