#include "minishell.h"

int	handle_single_heredoc(const char *delimiter, const char *file)
{
	int	fd;
	int	status;

	status = SUCCESS;
	fd = open(file, O_WRONLY);
	if (fd == -1)
		return (handle_system_error("open"));
	status = heredoc_content(fd, delimiter);
	close(fd);
	catch_child_signals();
	if (status == 130 || status == 131)
		unlink(file);
	return (status);
}

static char	*generate_temp_filename(void)
{
	static int	count = 0;
	char		*number;
	char		*name;

	while (1)
	{
		number = ft_itoa(count++);
		if (!number)
			return (NULL);
		name = ft_strjoin(".heredoc_", number);
		free(number);
		if (!name)
			return (NULL);
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
	}
}

char	*create_temp_file(void)
{
	char	*temp_name;
	int		fd;

	temp_name = generate_temp_filename();
	if (!temp_name)
		return (NULL);
	fd = open(temp_name, O_CREAT | O_RDWR | O_EXCL, 0644);
	if (fd == -1)
		return (free(temp_name), NULL);
	close(fd);
	return (temp_name);
}

static int	process_single_heredoc(t_redir *redir)
{
	char	*temp_file;
	int		status;

	temp_file = create_temp_file();
	if (!temp_file)
		return (MEMORY_ERROR);
	status = handle_single_heredoc(redir->file, temp_file);
	if (status != SUCCESS)
		return (free(temp_file), status);
	free(redir->file);
	redir->file = temp_file;
	return (SUCCESS);
}

int	process_heredocs(t_command *cmd)
{
	t_redir		*redir;
	int			status;
	t_command	*current;

	current = cmd;
	while (current)
	{
		if (current->redir)
		{
			redir = current->redir;
			while (redir)
			{
				if (redir->type == TOKEN_HEREDOC)
				{
					status = process_single_heredoc(redir);
					if (status != SUCCESS)
						return (status);
				}
				redir = redir->next;
			}
		}
		current = current->next;
	}
	return (SUCCESS);
}
