#include "minishell.h"

static void	handle_word_loop(char *input, int *i);
static int	handle_special_quote(t_token **tokens, int *i);

static int	handle_special_quote(t_token **tokens, int *i)
{
	t_token	*token;
	char	*str;

	str = ft_strdup("");
	if (!str)
		return (free_tokens(*tokens), FAILURE);
	token = create_token(TOKEN_WORD, str);
	if (!token)
		return (free_tokens(*tokens), FAILURE);
	append_token(tokens, token);
	*i += 2;
	return (SUCCESS);
}

int	handle_word(char *input, int *i, t_token **tokens)
{
	char	*str;
	int		start;
	int		len;
	t_token	*token;

	start = *i;
	if (ft_strncmp(input, "\"\"", 2) == 0 || ft_strncmp(input, "\'\'", 2) == 0)
		return (handle_special_quote(tokens, i));
	handle_word_loop(input, i);
	len = *i - start;
	str = malloc(len + 1);
	if (!str)
		return (free_tokens(*tokens), FAILURE);
	ft_strlcpy(str, input + start, len + 1);
	str[len] = '\0';
	token = create_token(TOKEN_WORD, str);
	if (!token)
		return (free_tokens(*tokens), FAILURE);
	append_token(tokens, token);
	return (SUCCESS);
}

static void	handle_word_loop(char *input, int *i)
{
	char	quote;

	while (input[*i] && !is_space(input[*i]) && !is_operator(input[*i]))
	{
		if (input[*i] == '\'' || input[*i] == '"')
		{
			quote = input[*i];
			(*i)++;
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
}
