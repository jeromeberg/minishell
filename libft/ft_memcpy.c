#include "libft.h"

/**
 * @brief Copy n bytes from src to dst (no overlap).
 * @param dst Destination memory area.
 * @param src Source memory area.
 * @param n Nb of bytes to copy.
 * @return Original value of dst.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;

	dest = (unsigned char *)dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)dest = *(unsigned char *)src;
		i++;
		src++;
		dest++;
	}
	return (dst);
}
