#include "minishell.h"

static int	change_dir(t_minishell *ms, const char *path)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("cd: getcwd");
		return (FAILURE);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (free(oldpwd), FAILURE);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("cd: getcwd");
		return (free(oldpwd), FAILURE);
	}
	envlst_update(ms, "OLDPWD", oldpwd, true);
	envlst_update(ms, "PWD", newpwd, true);
	free(oldpwd);
	free(newpwd);
	return (SUCCESS);
}

static int	ft_cd_home(t_minishell *ms)
{
	char	*home;

	home = envlst_get_value(ms, "HOME");
	if (!home)
	{
		printf("cd: HOME not set\n");
		return (FAILURE);
	}
	return (change_dir(ms, home));
}

int	ft_cd(t_minishell *ms, char **args, bool child)
{
	if (child == false)
	{
		if (!args[1])
			return (ft_cd_home(ms));
		return (change_dir(ms, args[1]));
	}
	return (SUCCESS);
}
