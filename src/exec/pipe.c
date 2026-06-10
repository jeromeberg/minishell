#include "minishell.h"

int	run_pipeline(t_command *cmd, t_pipe *pipe_array, int nb_of_pipes)
{
	t_command	*current;
	int			position;
	int			status;

	if (init_pipeline(nb_of_pipes, cmd) != SUCCESS)
		return (ERROR);
	current = cmd;
	position = 0;
	while (current)
	{
		cmd->pid_array[position] = fork_pipeline_process(current, position,
				pipe_array, nb_of_pipes);
		if (cmd->pid_array[position] == SYSCALL_ERROR)
		{
			cleanup_remaining_pipes(pipe_array, nb_of_pipes);
			free(cmd->pid_array);
			return (handle_system_error("fork"));
		}
		current = current->next;
		position++;
	}
	status = wait_for_processes(cmd->pid_array, nb_of_pipes + 1);
	cleanup_remaining_pipes(pipe_array, nb_of_pipes);
	return (status);
}

int	exec_pipe(t_command *cmd)
{
	int		status;
	int		nb_of_pipes;
	t_pipe	*pipe_array;

	nb_of_pipes = count_pipes(cmd);
	pipe_array = create_pipe_array(nb_of_pipes);
	if (!pipe_array)
		return (PIPE_ERROR);
	status = run_pipeline(cmd, pipe_array, nb_of_pipes);
	free(pipe_array);
	cleanup_fds(cmd);
	return (status);
}

int	wait_process_status(pid_t pid)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno != EINTR)
			return (handle_system_error("waitpid"));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n\n", 19);
		return (128 + WTERMSIG(status));
	}
	return (ERROR);
}

int	exec_simple(t_command *cmd, t_minishell *ms)
{
	pid_t	pid;
	int		status;

	status = prepare_exec(cmd);
	if (status != SUCCESS)
		return (handle_command_error(cmd, status));
	pid = fork();
	if (pid == SYSCALL_ERROR)
		return (handle_system_error("fork"));
	if (pid == 0)
		exec_in_child(cmd, ms);
	status = wait_process_status(pid);
	cleanup_fds(cmd);
	return (status);
}

int	exec_builtin(t_command *cmd, bool skip_redirections, bool child)
{
	const char	*cmd_name;
	int			status;

	cmd_name = get_cmd_name(cmd);
	if (!cmd_name)
		return (ERROR);
	if (cmd->redir && skip_redirections == false)
	{
		status = setup_redir(cmd);
		if (status != SUCCESS)
			return (status);
		status = get_builtin(cmd_name, cmd->args, cmd->ms, child);
		if (restore_fds(cmd) != SUCCESS)
			status = ERROR;
		return (status);
	}
	status = get_builtin(cmd_name, cmd->args, cmd->ms, child);
	if (child == true)
		free_cmd(cmd, true);
	return (status);
}
