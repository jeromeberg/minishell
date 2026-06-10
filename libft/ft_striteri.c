#include "libft.h"

/**
 * @brief Apply f to each character of s, passing its index.
 * @param s String to iterate.
 * @param f Function applied to each character (index, &char).
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
