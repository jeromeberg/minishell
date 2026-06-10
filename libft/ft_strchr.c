#include "libft.h"

/**
 * @brief Locate first occurrence of c in string s.
 * @param s String to search.
 * @param c Character to find.
 * @return Ptr to the located character, or NULL if not found.
 */
char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	ch;

	str = (char *)s;
	ch = (char)c;
	while (*str != ch)
	{
		if (*str == '\0')
		{
			if (ch == '\0')
				return (str);
			else
				return (NULL);
		}
		str++;
	}
	return (str);
}
