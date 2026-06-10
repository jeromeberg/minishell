#include "libft.h"

/**
 * @brief Compare s1 and s2 up to n characters.
 * @param s1 First string.
 * @param s2 Second string.
 * @param n Max nb of characters to compare.
 * @return 0 if equal, positive if s1 > s2, negative if s1 < s2.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
