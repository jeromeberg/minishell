#include "minishell.h"

int	check_syntax(t_token *curr, t_env *env)
{
	if (!curr || !curr->value)
		return (SUCCESS);
	if (is_redir(curr->type))
		return (check_redir(curr));
	if (curr->type == TOKEN_PIPE)
		return (check_pipe(curr));
	if ((is_directory(curr->value) || is_env_dir(curr->value, env))
		&& !curr->next && !curr->prev)
		return (check_other(curr, env));
	if (!curr->next && !curr->prev && is_special_char(curr->value[0]))
		return (check_other(curr, env));
	return (SUCCESS);
}

int	syntax_tokens(t_token *tokens, t_minishell *ms)
{
	t_token	*current;
	int		status;

	status = SUCCESS;
	current = tokens;
	while (current)
	{
		status = check_syntax(current, ms->envlst);
		if (status != SUCCESS)
		{
			change_exit_code(ms, status);
			return (status);
		}
		current = current->next;
	}
	return (SUCCESS);
}
