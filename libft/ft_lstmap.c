#include "libft.h"

/**
 * @brief Apply f to each node and build a new list.
 * @param lst Address of a ptr to a node.
 * @param f Function to apply on each content.
 * @param del Function to delete content if an allocation fails.
 * @return New list, or NULL if an allocation fails.
 */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;
	void	*temp_content;

	new_list = NULL;
	while (lst)
	{
		temp_content = f(lst->content);
		if (!temp_content)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_elem = ft_lstnew(temp_content);
		if (!new_elem)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}
