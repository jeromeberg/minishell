#include "libft.h"

/**
 * @brief Get length of string s
 * @param s String
 * @return Length of string s
 */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}
