#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (printf("No pwd\n"), FAILURE);
	printf("%s\n", pwd);
	return (free(pwd), SUCCESS);
}
