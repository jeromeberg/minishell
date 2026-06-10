#include "minishell.h"

int	print_error(const char *cmd_name, const char *arg, const char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd_name)
	{
		ft_putstr_fd((char *)cmd_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (arg)
	{
		ft_putstr_fd((char *)arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd((char *)msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (ERROR);
}

static int	handle_not_found_error(const char *cmd_name, t_env *env)
{
	if (!get_env_value(env, "PATH"))
		print_error(cmd_name, NULL, "No such file or directory");
	else
		print_error(NULL, cmd_name, "command not found");
	return (COMMAND_NOT_FOUND);
}

static int	handle_specific_error(const char *cmd_name, int error_code)
{
	if (error_code == PERMISSION_DENIED)
	{
		print_error(cmd_name, NULL, "Permission denied");
		return (PERMISSION_DENIED);
	}
	if (error_code == IS_DIR)
	{
		print_error(cmd_name, NULL, "Is a directory");
		return (IS_DIR);
	}
	return (ERROR);
}

int	handle_command_error(t_command *cmd, int error_code)
{
	const char	*cmd_name;

	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		cmd_name = "";
	if (error_code == COMMAND_NOT_FOUND)
		return (handle_not_found_error(cmd_name, cmd->ms->envlst));
	if (error_code == PERMISSION_DENIED || error_code == IS_DIR)
		return (handle_specific_error(cmd_name, error_code));
	if (errno)
		print_error(cmd_name, NULL, strerror(errno));
	return (ERROR);
}

int	handle_system_error(const char *syscall)
{
	print_error(syscall, NULL, strerror(errno));
	if (errno == ENOMEM)
		return (MEMORY_ERROR);
	return (ERROR);
}
