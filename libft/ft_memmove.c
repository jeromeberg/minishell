#include "libft.h"

/**
 * @brief Copy n bytes from src to dst, handling overlap.
 * @param dst Destination memory area.
 * @param src Source memory area.
 * @param n Nb of bytes to copy.
 * @return Original value of dst.
 */
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	if ((src == NULL && dst == NULL) || n == 0)
	{
		return (dst);
	}
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	i = 0;
	if (d > s)
	{
		while (n-- > 0)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
