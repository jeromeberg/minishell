#include "libft.h"

/**
 * @brief Return last node of the list.
 * @param lst Beginning of the list.
 * @return Ptr to last node, or NULL if list is empty.
 */
t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
