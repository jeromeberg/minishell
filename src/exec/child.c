#include "minishell.h"

char	*increment_shlvl(char *raw)
{
	char	*new_value;
	int		value;

	value = ft_atoi(raw + 6);
	if (value == INT_MAX)
		return (NULL);
	value++;
	new_value = ft_itoa(value);
	if (!new_value)
		return (NULL);
	return (ft_strjoin("SHLVL=", new_value));
}

static size_t	get_size_env(t_env *env)
{
	size_t	size;
	t_env	*current;

	size = 0;
	current = env;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

static char	**env_to_array(t_env *env, bool minishell)
{
	t_env	*current;
	char	**array;
	int		i;

	i = 0;
	current = env;
	array = malloc(sizeof(char *) * (get_size_env(env) + 1));
	if (!array)
		return (NULL);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "SHLVL") == 0 && minishell)
		{
			array[i++] = increment_shlvl(current->raw);
			if (!array[i - 1])
				return (free_tab(array), NULL);
		}
		else
			array[i++] = current->raw;
		current = current->next;
	}
	array[i] = NULL;
	return (array);
}

static void	setup_child_env(t_command *cmd, t_minishell *ms)
{
	char	**env_array;

	env_array = NULL;
	env_array = env_to_array(ms->envlst, ft_strcmp(cmd->args[0],
				"./minishell") == 0);
	if (!env_array)
	{
		cleanup_fds(cmd);
		free_all(ms, true);
		exit(MEMORY_ERROR);
	}
	execve(cmd->path, cmd->args, env_array);
	free_tab(env_array);
	cleanup_fds(cmd);
	free_all(ms, true);
	exit(handle_system_error("execve"));
}

void	exec_in_child(t_command *cmd, t_minishell *ms)
{
	setup_child_signals();
	if (cmd->redir)
	{
		if (setup_redir(cmd) != SUCCESS)
		{
			cleanup_fds(cmd);
			free_all(ms, true);
			exit(ERROR);
		}
	}
	setup_child_env(cmd, ms);
}
