#include "minishell.h"

static void	free_tab_partial(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**create_new_args(char **args, int size)
{
	char	**new_args;
	int		i;

	new_args = ft_calloc(sizeof(char *), size + 2);
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_args[i] = ft_strdup(args[i]);
		if (!new_args[i])
		{
			free_tab_partial(new_args, i);
			return (NULL);
		}
		i++;
	}
	return (new_args);
}

void	add_to_tab(t_token *token, t_command *cmd)
{
	char	**new_args;
	int		size;

	if (!token->value || !cmd)
		return ;
	size = 0;
	if (cmd->args)
		while (cmd->args[size])
			size++;
	new_args = create_new_args(cmd->args, size);
	if (!new_args)
		return ;
	new_args[size] = ft_strdup(token->value);
	if (!new_args[size])
	{
		free_tab_partial(new_args, size);
		return ;
	}
	new_args[size + 1] = NULL;
	if (cmd->args)
		free_tab(cmd->args);
	cmd->args = new_args;
}
