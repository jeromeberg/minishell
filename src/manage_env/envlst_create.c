#include "minishell.h"

static t_env	*envlst_new_node_without_equal(char *key);

t_env	*envlst_new_node(char *key, char *value)
{
	t_env	*new;
	char	*raw;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->has_equal = true;
	raw = ft_strjoin(key, "=");
	if (!raw)
	{
		free(new);
		return (NULL);
	}
	new->raw = ft_strjoin(raw, value);
	free(raw);
	if (!new->raw)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

static t_env	*envlst_new_node_without_equal(char *key)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup("");
	new->has_equal = false;
	new->raw = ft_strdup(key);
	if (!new->raw)
		return (NULL);
	new->next = NULL;
	return (new);
}

int	envlst_append(t_minishell *ms, t_env *new)
{
	t_env	*current;

	if (!new)
		return (FAILURE);
	if (!ms->envlst)
	{
		ms->envlst = new;
		return (SUCCESS);
	}
	current = ms->envlst;
	while (current && current->next)
		current = current->next;
	current->next = new;
	return (SUCCESS);
}

int	create_node(t_minishell *ms, char *key, char *value, bool has_equal)
{
	t_env	*node;

	if (has_equal)
		node = envlst_new_node(key, value);
	else
		node = envlst_new_node_without_equal(key);
	if (!node)
		return (FAILURE);
	envlst_append(ms, node);
	return (SUCCESS);
}
