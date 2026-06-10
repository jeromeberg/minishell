#include "libft.h"

/**
 * @brief Copy src into dest, NULL-terminating the result.
 * @param dest Destination buffer.
 * @param src Source string.
 * @param size Size of the destination buffer.
 * @return Length of src.
 */
size_t	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	size_t	i;

	i = 0;
	if (size)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
