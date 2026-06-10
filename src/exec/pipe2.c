#include "minishell.h"

void	clean_pipe(t_command *cmd, t_pipe *pipe_array, bool builtin)
{
	if (builtin == false)
		free_cmd(cmd, true);
	free(pipe_array);
	cleanup_fds(cmd);
}

void	execute_pipeline_command(t_command *cmd, t_pipe *pipe_array,
	int position, int nb_of_pipes)
{
	int	status;

	configure_pipe_fds(pipe_array, position, nb_of_pipes);
	close_unused_pipes(pipe_array, position, nb_of_pipes);
	if (cmd->redir)
	{
		status = setup_redir(cmd);
		if (status != SUCCESS)
			return (clean_pipe(cmd, pipe_array, false), exit(status));
	}
	if (is_builtin(cmd->args[0]))
		return (clean_pipe(cmd, pipe_array, true),
			exit(exec_builtin(cmd, true, true)));
	status = prepare_exec(cmd);
	if (status != SUCCESS)
		return (handle_command_error(cmd, status), free_cmd(cmd, true),
			free(pipe_array), exit(COMMAND_NOT_FOUND));
	if (execve(cmd->path, cmd->args, NULL) == SYSCALL_ERROR)
	{
		clean_pipe(cmd, pipe_array, false);
		cleanup_remaining_pipes(pipe_array, nb_of_pipes);
	}
	exit(handle_system_error("execve"));
}

static int	handle_parent_pipes(t_pipe *pipe_array, int position)
{
	if (position > 0)
	{
		if (close(pipe_array[position - 1][0]) == SYSCALL_ERROR)
			return (ERROR);
		if (close(pipe_array[position - 1][1]) == SYSCALL_ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	init_pipeline(int nb_of_pipes, t_command *cmd)
{
	cmd->pid_array = malloc(sizeof(pid_t) * (nb_of_pipes + 1));
	if (!cmd->pid_array)
		return (handle_system_error("malloc"));
	return (SUCCESS);
}

pid_t	fork_pipeline_process(t_command *cmd, int position,
		t_pipe *pipe_array, int nb_of_pipes)
{
	pid_t	pid;

	pid = fork();
	if (pid == SYSCALL_ERROR)
		return (SYSCALL_ERROR);
	if (pid == 0)
		execute_pipeline_command(cmd, pipe_array, position, nb_of_pipes);
	else
	{
		if (handle_parent_pipes(pipe_array, position) == ERROR)
		{
			cleanup_remaining_pipes(pipe_array, nb_of_pipes);
			return (SYSCALL_ERROR);
		}
	}
	return (pid);
}
