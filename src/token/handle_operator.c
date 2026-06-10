#include "minishell.h"

static int	handle_operator_out(char *input, int *i, t_token **tokens);
static int	handle_operator_in(char *input, int *i, t_token **tokens);

int	handle_operator(char *input, int *i, t_token **tokens)
{
	t_token	*new_token;
	char	*value;

	if (input[*i] == '|')
	{
		value = ft_strdup("|");
		if (!value)
			return (free_tokens(*tokens), FAILURE);
		new_token = create_token(TOKEN_PIPE, value);
		if (!new_token)
			return (free(value), free_tokens(*tokens), FAILURE);
		append_token(tokens, new_token);
		(*i)++;
	}
	else if (input[*i] == '<')
		return (handle_operator_in(input, i, tokens));
	else if (input[*i] == '>')
		return (handle_operator_out(input, i, tokens));
	return (SUCCESS);
}

static int	handle_operator_out(char *input, int *i, t_token **tokens)
{
	t_token	*new_token;
	char	*value;

	if (input[*i + 1] == '>')
	{
		value = ft_strdup(">>");
		if (!value)
			return (free_tokens(*tokens), FAILURE);
		new_token = create_token(TOKEN_APPEND, value);
		if (!new_token)
			return (free(value), free_tokens(*tokens), FAILURE);
		append_token(tokens, new_token);
		*i += 2;
		return (SUCCESS);
	}
	value = ft_strdup(">");
	if (!value)
		return (free_tokens(*tokens), FAILURE);
	new_token = create_token(TOKEN_OUTPUT, value);
	if (!new_token)
		return (free(value), free_tokens(*tokens), FAILURE);
	append_token(tokens, new_token);
	(*i)++;
	return (SUCCESS);
}

static int	handle_operator_in(char *input, int *i, t_token **tokens)
{
	t_token	*new_token;
	char	*value;

	if (input[*i + 1] == '<')
	{
		value = ft_strdup("<<");
		if (!value)
			return (free_tokens(*tokens), FAILURE);
		new_token = create_token(TOKEN_HEREDOC, value);
		if (!new_token)
			return (free(value), free_tokens(*tokens), FAILURE);
		append_token(tokens, new_token);
		*i += 2;
		return (SUCCESS);
	}
	value = ft_strdup("<");
	if (!value)
		return (free_tokens(*tokens), FAILURE);
	new_token = create_token(TOKEN_INPUT, value);
	if (!new_token)
		return (free(value), free_tokens(*tokens), FAILURE);
	append_token(tokens, new_token);
	(*i)++;
	return (SUCCESS);
}
