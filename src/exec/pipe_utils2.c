#include "minishell.h"

int	count_pipes(t_command *cmd)
{
	int			nb_of_pipes;
	t_command	*current;

	nb_of_pipes = 0;
	current = cmd;
	while (current)
	{
		nb_of_pipes++;
		current = current->next;
	}
	return (nb_of_pipes - 1);
}

t_pipe	*create_pipe_array(int nb_of_pipes)
{
	t_pipe	*pipe_array;
	int		i;

	pipe_array = malloc(sizeof(t_pipe) * nb_of_pipes);
	if (!pipe_array)
		return (NULL);
	i = 0;
	while (i < nb_of_pipes)
	{
		if (pipe(pipe_array[i]) == SYSCALL_ERROR)
		{
			while (--i >= 0)
			{
				if (close(pipe_array[i][0]) == SYSCALL_ERROR)
					exit(handle_system_error("close"));
				if (close(pipe_array[i][1]) == SYSCALL_ERROR)
					exit(handle_system_error("close"));
			}
			free(pipe_array);
			return (NULL);
		}
		i++;
	}
	return (pipe_array);
}

void	configure_pipe_fds(t_pipe *pipe_array, int cmd_pos, int nb_of_pipes)
{
	if (cmd_pos == 0)
	{
		if (dup2(pipe_array[cmd_pos][1], STDOUT_FILENO) == SYSCALL_ERROR)
			exit(handle_system_error("dup2"));
		close(pipe_array[cmd_pos][1]);
	}
	else if (cmd_pos == nb_of_pipes)
	{
		if (dup2(pipe_array[cmd_pos - 1][0], STDIN_FILENO) == SYSCALL_ERROR)
			exit(handle_system_error("dup2"));
		close(pipe_array[cmd_pos - 1][0]);
	}
	else
	{
		if (dup2(pipe_array[cmd_pos - 1][0], STDIN_FILENO) == SYSCALL_ERROR)
			exit(handle_system_error("dup2"));
		close(pipe_array[cmd_pos - 1][0]);
		if (dup2(pipe_array[cmd_pos][1], STDOUT_FILENO) == SYSCALL_ERROR)
			exit(handle_system_error("dup2"));
		close(pipe_array[cmd_pos][1]);
	}
}
