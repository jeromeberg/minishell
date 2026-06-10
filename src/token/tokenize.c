#include "minishell.h"

t_token	*ft_tokenize(t_minishell *ms)
{
	t_token	*tokens;
	int		i;
	int		status;

	tokens = NULL;
	i = 0;
	status = check_quotes(ms->line);
	while (ms->line[i] && status == SUCCESS)
	{
		if (is_space(ms->line[i]))
		{
			i++;
			continue ;
		}
		else if (is_operator(ms->line[i]))
		{
			status = handle_operator(ms->line, &i, &tokens);
			continue ;
		}
		else
			status = handle_word(ms->line, &i, &tokens);
	}
	return (tokens);
}
