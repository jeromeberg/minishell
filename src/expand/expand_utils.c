#include "minishell.h"

int	append_expanded_str(char **res, char *to_append)
{
	char	*tmp;

	if (!to_append)
		return (FAILURE);
	if (!*res)
	{
		*res = ft_strdup(to_append);
		free(to_append);
		if (!(*res))
			return (FAILURE);
		return (SUCCESS);
	}
	tmp = ft_strjoin(*res, to_append);
	free(to_append);
	if (!tmp)
		return (FAILURE);
	free(*res);
	*res = tmp;
	return (SUCCESS);
}

bool	is_double_quote(char c)
{
	if (c == '"')
		return (true);
	return (false);
}

bool	is_single_quote(char c)
{
	if (c == '\'')
		return (true);
	return (false);
}

bool	is_dollar_sign(char c)
{
	if (c == '$')
		return (true);
	return (false);
}
