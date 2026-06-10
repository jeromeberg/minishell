#include "minishell.h"

static char	*search_in_directory(char **directories, const char *cmd)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (directories[i])
	{
		tmp = ft_strjoin(directories[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, F_OK) == SYSCALL_SUCCESS)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static bool	is_path(const char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (cmd_name[0] == '/')
		return (true);
	if (cmd_name[0] == '.' && cmd_name[1] == '/')
		return (true);
	if (cmd_name[0] == '.' && cmd_name[1] == '.' && cmd_name[2] == '/')
		return (true);
	return (false);
}

char	*find_command_path(char *cmd_name, t_minishell *ms)
{
	char	*path;
	char	**directories;
	char	*full_path;

	if (cmd_name == NULL)
		return (NULL);
	if (is_path(cmd_name))
	{
		if (access(cmd_name, F_OK) == SYSCALL_SUCCESS)
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	path = get_env_value(ms->envlst, "PATH");
	if (path == NULL)
		return (NULL);
	directories = ft_split(path, ':');
	if (directories == NULL)
		return (NULL);
	full_path = search_in_directory(directories, cmd_name);
	free_tab(directories);
	return (full_path);
}

int	prepare_exec(t_command *cmd)
{
	char	*cmd_name;
	char	*path;

	cmd_name = get_cmd_name(cmd);
	if (!cmd_name || !*cmd_name)
		return (COMMAND_NOT_FOUND);
	path = find_command_path(cmd_name, cmd->ms);
	if (path == NULL)
		return (COMMAND_NOT_FOUND);
	if (access(path, X_OK) == SYSCALL_ERROR)
		return (free(path), PERMISSION_DENIED);
	if (set_cmd_path(cmd, path) != SUCCESS)
		return (free(path), ERROR);
	return (free(path), SUCCESS);
}
