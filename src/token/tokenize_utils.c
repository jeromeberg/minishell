#include "minishell.h"

bool	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	check_quotes(char *s)
{
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !d_quote)
			s_quote = !s_quote;
		else if (s[i] == '\"' && !s_quote)
			d_quote = !d_quote;
		i++;
	}
	if (d_quote != 0 || s_quote != 0)
		return (printf("%s", QUOTES_ERROR), FAILURE);
	return (SUCCESS);
}
