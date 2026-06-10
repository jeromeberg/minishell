#include "libft.h"

static int	is_set(char c, const char *set);

/**
 * @brief Trim characters in set from both ends of s1.
 * @param s1 String to trim.
 * @param set Characters to remove.
 * @return Trimmed string, or NULL if allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start < end && is_set(s1[start], set))
		start++;
	while (end > start && is_set(s1[end - 1], set))
		end--;
	len = end - start;
	return (ft_substr(s1, start, len));
}

static int	is_set(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set && set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

