#include "minishell.h"

int	execute_cmd_type(t_command *cmd, t_minishell *ms, char *cmd_name)
{
	int	status;

	if (is_simple_command(cmd) == false)
		status = exec_pipe(cmd);
	else if (is_builtin(cmd_name) == true)
		status = exec_builtin(cmd, false, false);
	else
		status = exec_simple(cmd, ms);
	set_exit_status(cmd, status);
	ms->exit_code = status;
	cleanup_heredoc_files(cmd);
	return (status);
}

int	execute_command(t_command *cmd, t_minishell *ms)
{
	char	*cmd_name;
	int		status;

	if (!cmd || !ms)
		return (ERROR);
	status = process_heredocs(cmd);
	if (status != SUCCESS)
		return (status);
	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		return (cleanup_heredoc_files(cmd), COMMAND_NOT_FOUND);
	status = execute_cmd_type(cmd, ms, cmd_name);
	return (status);
}
