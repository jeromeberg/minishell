#ifndef STRUCT_H
# define STRUCT_H
# include "minishell.h"

typedef int					t_pipe[2];
typedef int					(*t_builtin)(char **);
typedef struct s_token		t_token;
typedef struct s_ast		t_ast;
typedef struct s_command	t_command;

/* === ENV === */

typedef struct s_env
{
	char					*key;
	char					*value;
	char					*raw;
	bool					has_equal;
	struct s_env			*next;
}	t_env;	

/* === MINISHELL === */

typedef struct s_minishell
{
	char					*line;
	t_token					*tokens;
	t_ast					*ast;
	t_env					*envlst;
	int						exit_code;
	int						status;
	t_command				*command;
}	t_minishell;

/* === TOKEN === */

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INPUT,
	TOKEN_OUTPUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	struct s_token			*prev;
	struct s_token			*next;
}	t_token;

typedef struct s_redir
{
	struct s_redir			*next;
	t_token_type			type;
	char					*file;
}	t_redir;

typedef struct s_fd
{
	int						in;
	int						out;
	int						pipe_read;
	int						pipe_write;
	int						curr_in;
	int						curr_out;
	t_redir					*last_in;
	t_redir					*last_out;
}	t_fd;

typedef struct s_command
{
	struct s_command		*next;
	struct s_command		*prev;
	t_redir					*redir;
	char					**args;
	int						exit_status;
	t_fd					*fd;
	int						index;
	char					*path;
	t_minishell				*ms;
	pid_t					*pid_array;
}	t_command;

#endif
