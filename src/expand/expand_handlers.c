#include "minishell.h"

char	*handle_exit_expand(t_minishell *ms, int *i)
{
	char	*code;

	if (!ms->exit_code)
		code = ft_strdup("0");
	else
		code = ft_itoa(ms->exit_code);
	(*i) += 2;
	return (code);
}

char	*handle_var_expand(t_minishell *ms, char *str, int *i)
{
	int		start;
	size_t	len;
	char	*varname;
	char	*value;

	start = *i + 1;
	len = 0;
	while (str[start + len] && str[start + len] != ' '
		&& (ft_isalnum(str[start + len]) || str[start + len] == '_'))
		len++;
	varname = ft_substr(str, start, len);
	if (!varname)
		return (NULL);
	*i = start + len - 1;
	value = envlst_get_value(ms, varname);
	free(varname);
	(*i)++;
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

char	*handle_default(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && !is_single_quote(str[*i]) && !is_double_quote(str[*i])
		&& !is_dollar_sign(str[*i]))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}
