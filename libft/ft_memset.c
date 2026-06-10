#include "libft.h"

/**
 * @brief Fill len bytes of b with value c.
 * @param b Memory area to fill.
 * @param c Byte value to set.
 * @param len Nb of bytes to fill.
 * @return Original value of b.
 */
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}
