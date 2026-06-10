#include "minishell.h"

static char	*expand_string(t_minishell *ms, char *str);
static char	*handle_expander_status(int status, char **res);
int			dollar_sign_helper(t_minishell *ms, char *str, char **res, int *i);
void		double_quote_helper(char c, bool *is_quote, int *i);

static char	*handle_expander_status(int status, char **res)
{
	if (status == SUCCESS)
		return (*res);
	if (res)
		free(*res);
	return (NULL);
}

void	double_quote_helper(char c, bool *is_quote, int *i)
{
	if (is_double_quote(c))
	{
		*is_quote = !(*is_quote);
		(*i)++;
	}
}

int	dollar_sign_helper(t_minishell *ms, char *str, char **res, int *i)
{
	int	status;

	status = SUCCESS;
	if (is_dollar_sign(str[*i]) && (ft_isalnum(str[*i + 1])
			|| str[*i + 1] == '_'))
		return (append_expanded_str(res, handle_var_expand(ms, str, i)));
	else if (is_dollar_sign(str[*i]) && str[*i + 1] == '?')
		return (append_expanded_str(res, handle_exit_expand(ms, i)));
	else if (is_dollar_sign(str[*i]))
	{
		status = append_expanded_str(res, ft_substr(str, *i, 1));
		(*i)++;
	}
	return (status);
}

static char	*expand_string(t_minishell *ms, char *str)
{
	int		i;
	char	*res;
	int		status;
	bool	is_quote;

	res = NULL;
	i = 0;
	status = SUCCESS;
	is_quote = false;
	while (str[i] && status == SUCCESS)
	{
		double_quote_helper(str[i], &is_quote, &i);
		if (is_single_quote(str[i]))
			status = append_expanded_str(&res, handle_single_quote(str, &i,
						is_quote));
		status = dollar_sign_helper(ms, str, &res, &i);
		status = append_expanded_str(&res, handle_default(str, &i));
	}
	return (handle_expander_status(status, &res));
}

void	ft_expand(t_minishell *ms)
{
	t_token	*token;
	char	*expanded;

	if (!ms->tokens)
		return ;
	token = ms->tokens;
	while (token)
	{
		if (token->type == TOKEN_WORD && (ft_strchr(token->value, '$')
				|| ft_strchr(token->value, '"') || ft_strchr(token->value,
					'\'')))
		{
			expanded = expand_string(ms, token->value);
			if (!expanded)
				return (free(ms->tokens));
			free(token->value);
			token->value = expanded;
		}
		token = token->next;
	}
}
