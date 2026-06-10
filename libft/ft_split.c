#include "libft.h"

static char		**malloc_error(char **tab);
static size_t	count_words(char const *s, char c);
static size_t	next_word_len(char const *s, size_t start, char sep);

/**
 * @brief Split a string into an array of substrings.
 *
 * @param s String to split.
 * @param c Delimiter character.
 *
 * @return Newly allocated NULL-terminated array of substrings.
 * @retval NULL if allocation fails.
 */
char	**ft_split(const char *s, char c)
{
	char	**res;
	size_t	start;
	size_t	word_len;
	size_t	words;
	size_t	i;

	if (!s)
		return (NULL);
	start = 0;
	i = 0;
	words = count_words(s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	while (i < words)
	{
		while (s[start] && s[start] == c)
			start++;
		word_len = next_word_len(s, start, c);
		res[i] = ft_substr(s, start, word_len);
		if (!res[i])
			return (malloc_error(res));
		start += word_len;
		i++;
	}
	res[i] = NULL;
	return (res);
}

static char	**malloc_error(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	words;
	int		trigger;

	trigger = 0;
	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && !trigger)
		{
			trigger = 1;
			words++;
		}
		else if (s[i] == c)
			trigger = 0;
		i++;
	}
	return (words);
}

static size_t	next_word_len(const char *s, size_t start, char c)
{
	size_t	i;

	i = start;
	while (s[i] && s[i] != c)
		i++;
	return (i - start);
}
