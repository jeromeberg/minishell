#include "libft.h"

/**
 * @brief Locate needle in haystack, searching at most len bytes.
 * @param haystack String to search in.
 * @param needle String to find.
 * @param len Maximum number of bytes to search.
 * @return Ptr to the start of the match, or NULL if not found.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle == NULL || *needle == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
			{
				return ((char *)haystack + i);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}
