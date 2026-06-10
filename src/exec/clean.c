#include "minishell.h"

void	cleanup_heredoc_files(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC && redir->file)
			if (!ft_strncmp(redir->file, ".heredoc_", 9))
				unlink(redir->file);
		redir = redir->next;
	}
}

void	cleanup_remaining_pipes(t_pipe *pipe_array, int nb_of_pipes)
{
	int	i;

	i = 0;
	while (i < nb_of_pipes)
	{
		close(pipe_array[i][0]);
		close(pipe_array[i][1]);
		i++;
	}
}

void	cleanup_fds(t_command *cmd)
{
	if (!cmd || !cmd->fd)
		return ;
	if (cmd->fd->in > 2)
		close(cmd->fd->in);
	if (cmd->fd->out > 2)
		close(cmd->fd->out);
	if (cmd->fd->pipe_read > 2)
		close(cmd->fd->pipe_read);
	if (cmd->fd->pipe_write > 2)
		close(cmd->fd->pipe_write);
	cmd->fd->in = -1;
	cmd->fd->out = -1;
	cmd->fd->pipe_read = -1;
	cmd->fd->pipe_write = -1;
	cmd->fd->last_in = NULL;
	cmd->fd->last_out = NULL;
}
