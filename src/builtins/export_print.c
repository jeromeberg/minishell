#include "minishell.h"

static void	sort_keys(char **key_ordered, int size);
static void	copy_keys(t_env *src, char **key_ordered);
static void	print_env_ordered_loop(t_minishell *ms, char **key_ordered);

static void	sort_keys(char **key_ordered, int size)
{
	int		j;
	int		k;
	char	*tmp;

	j = 0;
	while (j < size - 1)
	{
		k = 0;
		while (k < size - j - 1)
		{
			if (ft_strcmp(key_ordered[k], key_ordered[k + 1]) > 0)
			{
				tmp = key_ordered[k];
				key_ordered[k] = key_ordered[k + 1];
				key_ordered[k + 1] = tmp;
			}
			k++;
		}
		j++;
	}
}

static void	copy_keys(t_env *src, char **key_ordered)
{
	int		i;
	t_env	*current;

	i = 0;
	current = src;
	while (current)
	{
		key_ordered[i++] = current->key;
		current = current->next;
	}
	key_ordered[i] = NULL;
}

static void	print_env_ordered_loop(t_minishell *ms, char **key_ordered)
{
	int		i;
	t_env	*current;

	i = 0;
	while (key_ordered[i])
	{
		current = envlst_get_env(ms, key_ordered[i]);
		if (current->has_equal)
			printf("export %s=\"%s\"\n", key_ordered[i], current->value);
		else
			printf("export %s\n", key_ordered[i]);
		i++;
	}
}

int	print_env_ordered(t_minishell *ms, t_env *src)
{
	char	**key_ordered;
	int		size;

	size = envlst_len(src);
	key_ordered = (char **)malloc(sizeof(char *) * (size + 1));
	if (!key_ordered)
		return (printf("malloc"), FAILURE);
	copy_keys(src, key_ordered);
	sort_keys(key_ordered, size);
	print_env_ordered_loop(ms, key_ordered);
	free(key_ordered);
	return (SUCCESS);
}
