#include "minishell.h"

bool	is_special_char(char c)
{
	return (c == '!' || c == '#' || c == ':');
}

int	is_directory(char *token)
{
	struct stat	st;

	if (!token || !token[0])
		return (0);
	if (ft_strcmp(token, "$HOME") == 0)
		return (1);
	if (access(token, F_OK) == -1)
		return (0);
	else if (stat(token, &st) == -1)
	{
		perror("stat");
		return (1);
	}
	if (S_ISDIR(st.st_mode))
		return (1);
	return (0);
}

void	change_exit_code(t_minishell *ms, int status)
{
	ms->exit_code = status;
}

bool	is_redir(t_token_type type)
{
	return (type == TOKEN_INPUT || type == TOKEN_OUTPUT || type == TOKEN_APPEND
		|| type == TOKEN_HEREDOC);
}

int	syntax_error(const char *token)
{
	if (token)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `",
			STDERR_FILENO);
		ft_putstr_fd((char *)token, STDERR_FILENO);
		ft_putendl_fd("'\n", STDERR_FILENO);
	}
	else
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
	return (SYNTAX_ERROR);
}
