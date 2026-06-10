#include "minishell.h"

t_command	*create_cmd(t_minishell *ms)
{
	t_command	*cmd;

	cmd = ft_calloc(sizeof(t_command), 1);
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->args = NULL;
	cmd->redir = NULL;
	cmd->exit_status = 0;
	cmd->path = NULL;
	cmd->ms = ms;
	cmd->pid_array = NULL;
	cmd->fd = ft_calloc(sizeof(t_fd), 1);
	if (!cmd->fd)
		return (free(cmd), cmd = NULL, NULL);
	init_fd(cmd->fd);
	return (cmd);
}

static void	extend_cmd(t_command **cmd, t_minishell *ms)
{
	(*cmd)->next = create_cmd(ms);
	(*cmd)->next->prev = *cmd;
	(*cmd)->next->index = (*cmd)->index + 1;
	(*cmd) = (*cmd)->next;
}

static t_command	*init_command(t_minishell *ms)
{
	t_command	*cmd;

	cmd = create_cmd(ms);
	cmd->index = 0;
	return (cmd);
}

void	process_parsing(t_command *cmd, t_token *tokens, t_minishell *ms)
{
	while (tokens)
	{
		if (tokens->type == TOKEN_WORD)
			add_to_tab(tokens, cmd);
		else if (tokens->type == TOKEN_PIPE)
			extend_cmd(&cmd, ms);
		else if (is_redir(tokens->type))
			handle_redir(cmd, &tokens);
		tokens = tokens->next;
	}
}

t_command	*parse(t_token *tokens, t_minishell *ms)
{
	t_command	*head;
	t_token		*temp;

	head = NULL;
	temp = tokens;
	head = init_command(ms);
	if (!head)
		return (NULL);
	process_parsing(head, temp, ms);
	if (check_heredoc_count(head) == FAILURE)
		return (free_cmd(head, false), NULL);
	return (head);
}
