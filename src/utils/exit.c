#include "minishell.h"

void	exit_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void	free_all(t_minishell *ms, bool token)
{
	if (ms->line)
		free(ms->line);
	if (token && ms->tokens)
		free_tokens(ms->tokens);
	if (ms->command)
		free_cmd(ms->command, false);
	if (ms->envlst)
		free_env(ms->envlst);
}

void	exit_status(t_minishell *ms)
{
	int	status;

	status = ms->exit_code;
	exit(status);
}
