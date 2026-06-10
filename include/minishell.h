#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <ctype.h>
# include <stdbool.h>
# include <limits.h>
# include <termios.h>
# include <errno.h>
# include "errors.h"
# include "../libft/libft.h"
# include "struct.h"

# define PROMPT "minishell$ "
# define HEREDOC_PROMPT ">"

extern volatile int	g_sig_status;

/* === ENV === */

t_env				*init_env(t_minishell *ms, char **envp);
t_env				*envlst_new_node(char *key, char *value);
bool				envlst_key_exists(t_minishell *ms, char *key);
char				*envlst_get_value(t_minishell *ms, char *key);
t_env				*envlst_get_env(t_minishell *ms, char *key);
int					envlst_append(t_minishell *ms, t_env *new);
int					envlst_update(t_minishell *ms, char *key, char *value,
						bool create);
bool				is_valid_key(char *key);
int					envlst_remove(t_minishell *ms, char *key);
void				free_env(t_env *envlst);
int					envlst_update_without_equal(t_minishell *ms, char *key,
						bool create);
int					envlst_len(t_env *src);
int					create_node(t_minishell *ms, char *key, char *value,
						bool has_equal);

/* === TOKEN === */

t_token				*ft_tokenize(t_minishell *ms);
int					handle_operator(char *input, int *i, t_token **tokens);
int					handle_word(char *input, int *i, t_token **tokens);
t_token				*create_token(t_token_type type, char *value);
void				append_token(t_token **head, t_token *new_token);

void				free_tokens(t_token *tokens);

bool				is_operator(char c);
bool				is_space(char c);
int					check_quotes(char *s);

/* === SYNTAX === */

int					syntax_tokens(t_token *tokens, t_minishell *ms);

int					check_redir(t_token *token);
int					check_pipe(t_token *token);
int					check_other(t_token *token, t_env *env);

void				change_exit_code(t_minishell *ms, int status);
int					syntax_error(const char *token);
bool				is_redir(t_token_type type);
int					is_directory(char *token);
bool				is_special_char(char c);
bool				is_env_dir(char *token, t_env *env);
char				*get_env_value(t_env *env, char *token);

/* === EXPANDER === */

void				ft_expand(t_minishell *ms);
bool				is_double_quote(char c);
bool				is_single_quote(char c);
bool				is_dollar_sign(char c);
int					append_expanded_str(char **res, char *to_append);
char				*handle_exit_expand(t_minishell *ms, int *i);
char				*handle_var_expand(t_minishell *ms, char *str, int *i);
char				*handle_single_quote(char *str, int *i, bool is_quote);
char				*handle_default(char *str, int *i);

/* === EXEC === */

bool				is_builtin(char *cmd);
int					execute_command(t_command *cmd, t_minishell *ms);

char				*get_cmd_name(t_command *cmd);
int					get_exit_status(t_command *cmd);
char				*get_cmd_path(t_command *cmd);
int					get_builtin(const char *cmd_name, char **args,
						t_minishell *ms, bool child);

int					exec_pipe(t_command *cmd);
int					exec_simple(t_command *cmd, t_minishell *ms);
int					exec_builtin(t_command *cmd, bool skip_redirections,
						bool child);

int					init_pipeline(int nb_of_pipes, t_command *cmd);
int					prepare_exec(t_command *cmd);
void				exec_in_child(t_command *cmd, t_minishell *ms);

int					count_pipes(t_command *cmd);
t_pipe				*create_pipe_array(int nb_of_pipes);
void				configure_pipe_fds(t_pipe *pipe_array, int cmd_pos,
						int nb_of_pipes);

int					process_heredocs(t_command *cmd);
int					heredoc_content(int fd, const char *delimiter);
void				cleanup_heredoc_files(t_command *cmd);

int					setup_redir(t_command *cmd);
int					restore_fds(t_command *cmd);
int					apply_input_redir(t_command *cmd);
int					apply_output_redir(t_command *cmd);
void				handle_input_redir(t_fd *cmd_fd, t_redir *redir);
void				handle_output_redir(t_fd *cmd_fd, t_redir *redir);
void				initialize_fd(t_fd *fd);

bool				is_simple_command(t_command *cmd);
bool				is_valid_command(t_command *cmd);
int					set_cmd_path(t_command *cmd, char *path);
void				set_exit_status(t_command *cmd, int status);

void				cleanup_remaining_pipes(t_pipe *pipe_array,
						int nb_of_pipes);
void				cleanup_fds(t_command *cmd);

void				close_unused_pipes(t_pipe *pipe_array, int cmd_position,
						int nb_of_pipes);
int					wait_for_processes(pid_t *pids, int count);
pid_t				fork_pipeline_process(t_command *cmd, int position,
						t_pipe *pipe_array, int nb_of_pipes);

/* === PARSING === */

void				add_to_tab(t_token *token, t_command *cmd);
void				handle_redir(t_command *cmd, t_token **token);
t_command			*parse(t_token *tokens, t_minishell *ms);
void				free_cmd(t_command *cmd, bool ms_aussi);
void				init_fd(t_fd *fd);
int					check_heredoc_count(t_command *cmd);

/* === UTILS === */

void				free_tab(char **tab);
void				exit_error(char *msg);
int					ft_strcmp(const char *s1, const char *s2);

/* === UTILS/EXIT === */

void				exit_status(t_minishell *ms);
void				exit_error(char *msg);
void				free_all(t_minishell *ms, bool token);
int					handle_command_error(t_command *cmd, int error_code);
int					handle_system_error(const char *syscall);

/* === SIGNALS === */

void				setup_signals(void);
void				setup_child_signals(void);
void				catch_child_signals(void);

/* === BUILTINS === */

int					ft_cd(t_minishell *ms, char **args, bool child);
int					ft_echo(char **args);
int					ft_env(t_minishell *ms);
int					ft_export(t_minishell *ms, char **args, bool child);
int					ft_pwd(void);
int					ft_unset(t_minishell *ms, char **args, bool child);
int					ft_exit(t_minishell *ms, char **args, bool child);
int					print_env_ordered(t_minishell *ms, t_env *src);

#endif
