#include "libft.h"

/**
 * @brief Allocate memory for count objects of size bytes, zeroed.
 * @param count Nb of objects.
 * @param size Size of each object in bytes.
 * @return Ptr to allocated memory, or NULL on failure.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (((long long)count < 0 && size != 0) || ((long long)size < 0
			&& count != 0))
		return (NULL);
	if (((long long)count * (long long)size) > 4294967295)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}
