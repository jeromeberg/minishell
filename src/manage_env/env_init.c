#include "minishell.h"

static t_env	*copy_envp_to_envlst(t_minishell *ms, char **envp);
static t_env	*set_default_envp(t_minishell *ms);
static void		parse_envp_entry(char **key, char **value, char *envp);

t_env	*init_env(t_minishell *ms, char **envp)
{
	if (!envp || !envp[0])
		return (set_default_envp(ms));
	else
		return (copy_envp_to_envlst(ms, envp));
}

static t_env	*set_default_envp(t_minishell *ms)
{
	t_env	*shlvl;
	t_env	*pwd;
	char	*cwd;
	char	*raw;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (printf("getcwd failed\n"), NULL);
	raw = ft_strjoin("PWD=", cwd);
	if (!raw)
		return (free(cwd), NULL);
	pwd = envlst_new_node("PWD", cwd);
	free(cwd);
	if (!pwd)
		return (NULL);
	raw = ft_strdup("SHLVL=1");
	if (!raw)
		return (free(pwd), NULL);
	shlvl = envlst_new_node("SHLVL", "1");
	if (!shlvl)
		return (free(pwd), NULL);
	envlst_append(ms, pwd);
	envlst_append(ms, shlvl);
	return (ms->envlst);
}

static void	parse_envp_entry(char **key, char **value, char *envp)
{
	*key = NULL;
	*value = NULL;
	if (ft_strchr(envp, '='))
	{
		*key = ft_substr(envp, 0, ft_strchr(envp, '=') - envp);
		if (!*key)
		{
			*key = NULL;
			return ;
		}
		*value = ft_strdup(ft_strchr(envp, '=') + 1);
		if (!*value)
		{
			free(*key);
			*key = NULL;
		}
		return ;
	}
	*key = ft_strdup(envp);
	if (!*key)
		*key = NULL;
	*value = NULL;
}

static t_env	*copy_envp_to_envlst(t_minishell *ms, char **envp)
{
	char	*key;
	char	*value;
	t_env	*node;
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		parse_envp_entry(&key, &value, envp[i]);
		if (!key)
			return (free(ms->envlst), NULL);
		node = envlst_new_node(key, value);
		if (value)
			free(value);
		free(key);
		if (!node)
			return (free_env(ms->envlst), NULL);
		envlst_append(ms, node);
		i++;
	}
	return (ms->envlst);
}
