#include "libft.h"

/**
 * @brief Duplicate a string.
 * @param s1 String to duplicate.
 * @return Newly allocated copy of s1, or NULL on failure.
 */
char	*ft_strdup(char *s1)
{
	size_t	i;
	size_t	len;
	char	*dest;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
