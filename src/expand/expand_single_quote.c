#include "minishell.h"

static bool	is_single_quote_closed(const char *str, int i);

static bool	is_single_quote_closed(const char *str, int i)
{
	while (str[i])
	{
		if (is_single_quote(str[i]))
			return (true);
		i++;
	}
	return (false);
}

static char	*handle_sq_in_double(char *str, int *i)
{
	bool	closed;
	char	*res;
	int		start;

	closed = is_single_quote_closed(str, *i + 1);
	if (!closed)
	{
		res = ft_substr(str, *i, 1);
		(*i)++;
		return (res);
	}
	else
	{
		start = *i;
		(*i)++;
		while (str[*i] && !is_single_quote(str[*i]))
			(*i)++;
		if (is_single_quote(str[*i]))
			(*i)++;
		return (ft_substr(str, start, *i - start));
	}
}

char	*handle_single_quote(char *str, int *i, bool is_quote)
{
	int		start;
	char	*res;

	if (is_quote)
	{
		return (handle_sq_in_double(str, i));
	}
	else
	{
		(*i)++;
		start = *i;
		while (str[*i] && !is_single_quote(str[*i]))
			(*i)++;
		res = ft_substr(str, start, *i - start);
		if (is_single_quote(str[*i]))
			(*i)++;
	}
	return (res);
}
