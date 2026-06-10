#include "minishell.h"

static bool	is_n_flag(char *arg)
{
	int	j;

	j = 1;
	if (!arg || arg[0] != '-' || arg[1] == '\0')
		return (false);
	while (arg[j] && arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

static int	skip_n_flags(char **args, bool *newline)
{
	int	i;

	i = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		*newline = false;
		i++;
	}
	return (i);
}

static void	print_arguments(char **args, int start)
{
	int	i;

	i = start;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
}

int	ft_echo(char **args)
{
	bool	newline;
	int		i;

	newline = true;
	i = skip_n_flags(args, &newline);
	print_arguments(args, i);
	if (newline)
		printf("\n");
	return (SUCCESS);
}
