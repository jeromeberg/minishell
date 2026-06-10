#include "minishell.h"

void	initialize_fd(t_fd *fd)
{
	fd->curr_in = -1;
	fd->curr_out = -1;
	fd->last_in = NULL;
	fd->last_out = NULL;
}

void	handle_input_redir(t_fd *cmd_fd, t_redir *redir)
{
	cmd_fd->curr_in = 1;
	cmd_fd->last_in = redir;
}

void	handle_output_redir(t_fd *cmd_fd, t_redir *redir)
{
	int	flags;
	int	fd;

	if (redir->type == TOKEN_OUTPUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(redir->file, flags, 0644);
	if (fd != -1)
		close(fd);
	cmd_fd->curr_out = 1;
	cmd_fd->last_out = redir;
}

int	apply_input_redir(t_command *cmd)
{
	int		new_fd;
	char	*file;

	file = cmd->fd->last_in->file;
	new_fd = open(file, O_RDONLY);
	if (new_fd == SYSCALL_ERROR)
		return (handle_system_error("open"));
	if (dup2(new_fd, STDIN_FILENO) == SYSCALL_ERROR)
	{
		close(new_fd);
		return (handle_system_error("dup2"));
	}
	close(new_fd);
	return (SUCCESS);
}

int	apply_output_redir(t_command *cmd)
{
	int				new_fd;
	int				flags;
	t_token_type	type;
	char			*file;

	type = cmd->fd->last_out->type;
	file = cmd->fd->last_out->file;
	if (type == TOKEN_OUTPUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	new_fd = open(file, flags, 0644);
	if (new_fd == SYSCALL_ERROR)
		return (handle_system_error("open"));
	if (dup2(new_fd, STDOUT_FILENO) == SYSCALL_ERROR)
	{
		close(new_fd);
		return (handle_system_error("dup2"));
	}
	close(new_fd);
	return (SUCCESS);
}
