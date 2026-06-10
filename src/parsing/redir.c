#include "minishell.h"

static t_redir	*create_redir(t_token_type type, char *file)
{
	t_redir	*redir;

	redir = ft_calloc(sizeof(t_redir), 1);
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

static void	add_redir_to_cmd(t_command *cmd, t_redir *new_redir)
{
	t_redir	*tmp;

	if (!cmd || !new_redir)
		return ;
	if (!cmd->redir)
	{
		cmd->redir = new_redir;
		return ;
	}
	tmp = cmd->redir;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
}

void	handle_redir(t_command *cmd, t_token **token)
{
	t_redir			*new_redir;
	t_token_type	type;

	if (!token || !*token || !(*token)->next)
		return ;
	type = (*token)->type;
	*token = (*token)->next;
	if ((*token)->type != TOKEN_WORD)
		return ;
	new_redir = create_redir(type, (*token)->value);
	if (!new_redir)
		return ;
	add_redir_to_cmd(cmd, new_redir);
}
