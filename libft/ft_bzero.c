#include "libft.h"

/**
 * @brief Write n zeroed bytes to s.
 * @param s Ptr to memory area.
 * @param n Nb of bytes to zero.
 */
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
