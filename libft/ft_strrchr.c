#include "libft.h"

/**
 * @brief Locate last occurrence of c in string s.
 * @param s String to search.
 * @param c Character to find.
 * @return Ptr to the located character, or NULL if not found.
 */
char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	char	*str;
	char	*last;

	str = (char *)s;
	ch = (char)c;
	last = NULL;
	while (*str)
	{
		if (*str == ch)
		{
			last = str;
		}
		str++;
	}
	if (ch == '\0')
	{
		return (str);
	}
	return (last);
}
