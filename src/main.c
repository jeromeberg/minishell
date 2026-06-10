#include "minishell.h"

volatile int	g_sig_status = 0;

void	set_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

int	init_ms(t_minishell *ms, char **envp)
{
	ms->line = NULL;
	ms->ast = NULL;
	ms->tokens = NULL;
	ms->exit_code = 0;
	ms->envlst = NULL;
	ms->status = 0;
	ms->command = NULL;
	ms->envlst = init_env(ms, envp);
	if (!ms->envlst)
		return (FAILURE);
	return (SUCCESS);
}

void	process_line(t_minishell *ms)
{
	ms->tokens = ft_tokenize(ms);
	if (ms->tokens)
	{
		if (syntax_tokens(ms->tokens, ms) == SUCCESS)
		{
			ft_expand(ms);
			if (ms->tokens)
			{
				ms->command = parse(ms->tokens, ms);
				free_tokens(ms->tokens);
				ms->tokens = NULL;
				if (ms->command)
				{
					ms->status = execute_command(ms->command, ms);
					free_cmd(ms->command, false);
				}
			}
		}
		if (ms->tokens)
			free_tokens(ms->tokens);
		ms->tokens = NULL;
	}
}

int	loop(t_minishell *ms)
{
	while (1)
	{
		setup_signals();
		g_sig_status = 0;
		ms->line = readline(PROMPT);
		if (!ms->line)
			return (ft_putendl_fd("exit", STDERR_FILENO), ms->exit_code);
		if (*ms->line)
		{
			catch_child_signals();
			add_history(ms->line);
			process_line(ms);
		}
		free(ms->line);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	ms;
	int			status;

	(void)argc;
	(void)argv;
	set_signals();
	if (init_ms(&ms, envp) != SUCCESS)
		return (EXIT_FAILURE);
	status = loop(&ms);
	free_env(ms.envlst);
	if (status != SUCCESS)
		exit_status(&ms);
	return (0);
}
