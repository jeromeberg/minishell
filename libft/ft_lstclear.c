#include "libft.h"

/**
 * @brief Delete and free the list.
 * @param lst Address of a ptr to a node.
 * @param del Function used to delete each node's content.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*next;

	if (lst != NULL && del != NULL)
	{
		tmp = *lst;
		while (tmp != NULL)
		{
			next = tmp->next;
			del(tmp->content);
			free(tmp);
			tmp = next;
		}
		*lst = NULL;
	}
}
