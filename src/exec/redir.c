#include "minishell.h"

int	manage_redir(t_command *cmd)
{
	int	status;

	if (cmd->fd->curr_in > 0)
	{
		status = apply_input_redir(cmd);
		if (status != SUCCESS)
			return (status);
	}
	if (cmd->fd->curr_out > 0)
	{
		status = apply_output_redir(cmd);
		if (status != SUCCESS)
		{
			restore_fds(cmd);
			return (status);
		}
	}
	return (SUCCESS);
}

void	find_final_redir(t_command *cmd)
{
	t_redir	*current;

	initialize_fd(cmd->fd);
	current = cmd->redir;
	while (current)
	{
		if (current->type == TOKEN_INPUT || current->type == TOKEN_HEREDOC)
			handle_input_redir(cmd->fd, current);
		else if (current->type == TOKEN_OUTPUT || current->type == TOKEN_APPEND)
			handle_output_redir(cmd->fd, current);
		current = current->next;
	}
}

int	restore_fds(t_command *cmd)
{
	if (dup2(cmd->fd->in, STDIN_FILENO) == SYSCALL_ERROR)
	{
		close(cmd->fd->in);
		return (handle_system_error("dup2"));
	}
	if (dup2(cmd->fd->out, STDOUT_FILENO) == SYSCALL_ERROR)
	{
		close(cmd->fd->out);
		return (handle_system_error("dup2"));
	}
	close(cmd->fd->in);
	close(cmd->fd->out);
	return (SUCCESS);
}

int	save_fd(t_command *cmd)
{
	int	fd_in;
	int	fd_out;

	fd_in = dup(STDIN_FILENO);
	if (fd_in == SYSCALL_ERROR)
		return (handle_system_error("dup"));
	fd_out = dup(STDOUT_FILENO);
	if (fd_out == SYSCALL_ERROR)
	{
		close(fd_in);
		return (handle_system_error("dup"));
	}
	cmd->fd->in = fd_in;
	cmd->fd->out = fd_out;
	return (SUCCESS);
}

int	setup_redir(t_command *cmd)
{
	int	status;

	if (!cmd->fd)
		return (ERROR);
	status = save_fd(cmd);
	if (status != SUCCESS)
		return (status);
	find_final_redir(cmd);
	status = manage_redir(cmd);
	if (status != SUCCESS)
	{
		cleanup_fds(cmd);
		return (status);
	}
	return (SUCCESS);
}
