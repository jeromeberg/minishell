#include "minishell.h"

void	free_redir(t_redir *redirections)
{
	t_redir	*tmp;

	while (redirections)
	{
		tmp = redirections;
		redirections = redirections->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
	}
}

void	free_cmd(t_command *cmd, bool ms_aussi)
{
	t_command	*tmp;

	if (ms_aussi)
	{
		if (cmd->ms->envlst)
			free_env(cmd->ms->envlst);
		if (cmd->pid_array)
			free(cmd->pid_array);
	}
	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
			free_tab(tmp->args);
		if (tmp->redir)
			free_redir(tmp->redir);
		if (tmp->fd)
			free(tmp->fd);
		if (tmp->path)
			free(tmp->path);
		free(tmp);
	}
	cmd = NULL;
}

int	check_heredoc_count(t_command *cmd)
{
	t_redir	*redir;
	int		count;

	count = 0;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
				count++;
			if (count > 16)
				return (FAILURE);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

void	init_fd(t_fd *fd)
{
	fd->in = -1;
	fd->out = -1;
	fd->pipe_read = -1;
	fd->pipe_write = -1;
	fd->curr_in = -1;
	fd->curr_out = -1;
	fd->last_in = NULL;
	fd->last_out = NULL;
}
