#include "libft.h"

/**
 * @brief Free the content and the node itself.
 * @param lst Node to free.
 * @param del Function used to delete the content.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		del(lst->content);
		free(lst);
	}
	return ;
}
