#include "libft.h"

/**
 * @brief Create a substring from a string.
 *
 * Allocates and returns a substring from s. The substring starts at index
 * start and has a maximum length of len.
 *
 * @param s Source string.
 * @param start Start index in s.
 * @param len Max length of the substring.
 *
 * @return Newly allocated substring, or NULL if allocation fails.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;
	size_t	j;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if ((size_t)start >= s_len)
		len = 0;
	else if (len > s_len - (size_t)start)
		len = s_len - (size_t)start;
	dst = (char *)malloc(sizeof(char) * ((len) + 1));
	if (!dst)
		return (NULL);
	i = start;
	j = 0;
	while (i < s_len && j < len)
		dst[j++] = s[i++];
	dst[j] = '\0';
	return (dst);
}
