#include "minishell.h"

int	check_redir(t_token *token)
{
	if (!token->next)
		return (syntax_error("newline"));
	if (token->next->type != TOKEN_WORD)
		return (syntax_error(token->next->value));
	return (SUCCESS);
}

int	check_pipe(t_token *token)
{
	if (!token->prev)
		return (syntax_error("|"));
	if (!token->next)
		return (syntax_error("newline"));
	return (SUCCESS);
}

static int	print_dir_error(char *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd(": is a directory\n", STDERR_FILENO);
	return (IS_DIR);
}

int	check_other(t_token *token, t_env *env)
{
	char	*expanded;

	if (is_special_char(token->value[0]) && token->value[1] == '\0')
	{
		if (token->value[0] == '!')
			return (ERROR);
		return (69);
	}
	if (!ft_strcmp(token->value, "$HOME"))
	{
		expanded = get_env_value(env, "HOME");
		if (!expanded || !*expanded)
			return (ERROR);
		return (print_dir_error(expanded));
	}
	return (print_dir_error(token->value));
}
