#include "libft.h"

/**
 * @brief Append src to dst, NULL-terminating and limiting total size to n.
 * @param dst Destination buffer (must be NULL-terminated).
 * @param src Source string to append.
 * @param n Total size of destination buffer.
 * @return Length of dst and src (strlen(dst) + strlen(src)).
 */
size_t	ft_strlcat(char *dst, char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < n)
		i++;
	while (src[j] != '\0' && (i + j + 1) < n)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < n)
		dst[i + j] = 0;
	return (i + ft_strlen(src));
}
