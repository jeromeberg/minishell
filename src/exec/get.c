#include "minishell.h"

char	*get_cmd_name(t_command *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (NULL);
	return (cmd->args[0]);
}

int	get_exit_status(t_command *cmd)
{
	if (!cmd)
		return (ERROR);
	return (cmd->exit_status);
}

char	*get_cmd_path(t_command *cmd)
{
	if (!cmd)
		return (NULL);
	return (cmd->path);
}

int	get_builtin(const char *cmd_name, char **args, t_minishell *ms, bool child)
{
	int	status;

	status = SUCCESS;
	if (!ft_strcmp(cmd_name, "echo"))
		status = ft_echo(args);
	else if (!ft_strcmp(cmd_name, "cd"))
		status = ft_cd(ms, args, child);
	else if (!ft_strcmp(cmd_name, "pwd"))
		status = ft_pwd();
	else if (!ft_strcmp(cmd_name, "export"))
		status = ft_export(ms, args, child);
	else if (!ft_strcmp(cmd_name, "unset"))
		status = ft_unset(ms, args, child);
	else if (!ft_strcmp(cmd_name, "env"))
		status = ft_env(ms);
	else if (!ft_strcmp(cmd_name, "exit"))
		status = ft_exit(ms, args, child);
	return (status);
}
