#include "get_next_line.h"

int	ft_nl_found(char *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	if (!c)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_str_join_gnl(char *s1, char *s2)
{
	char	*new_str;
	size_t	len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = malloc(sizeof (char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	free(s1);
	j = 0;
	while (s2 && s2[j])
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[len] = 0;
	return (new_str);
}

char	*ft_strcpy_nl(char *dest, char *src, int nl_found)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		if (src[i] == '\n' && nl_found)
		{
			i++;
			break;
		}
		i++;
	}
	dest[i] = 0;
	return (dest);
}
