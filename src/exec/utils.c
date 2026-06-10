#include "minishell.h"

void	set_exit_status(t_command *cmd, int status)
{
	if (cmd)
		cmd->exit_status = status;
}

int	set_cmd_path(t_command *cmd, char *path)
{
	if (!cmd)
		return (ERROR);
	cmd->path = ft_strdup(path);
	if (!cmd->path)
		return (ERROR);
	return (SUCCESS);
}

bool	is_simple_command(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (false);
	if (cmd->next == NULL)
		return (true);
	else
		return (false);
}

bool	is_valid_command(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (false);
	return (true);
}
