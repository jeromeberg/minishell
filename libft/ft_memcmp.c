#include "libft.h"

/**
 * @brief Compare first n bytes of s1 and s2.
 * @param s1 First memory area.
 * @param s2 Second memory area.
 * @param n Nb of bytes to compare.
 * @return 0 if equal, positive if s1 > s2, negative if s1 < s2.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
