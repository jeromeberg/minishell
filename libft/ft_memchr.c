#include "libft.h"

/**
 * @brief Locate first occurrence of c in first n bytes of s.
 * @param s Memory area to search.
 * @param c Byte to locate.
 * @param n Nb of bytes to search.
 * @return Ptr to the located byte, or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == (unsigned char)c)
			return (str);
		str++;
	}
	return (NULL);
}
