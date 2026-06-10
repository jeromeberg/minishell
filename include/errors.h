#ifndef ERRORS_H
# define ERRORS_H

# define MALLOC_ERROR -2

# define SYSCALL_ERROR -1
# define SYSCALL_SUCCESS 0

// basic returns
# define SUCCESS 0
# define FAILURE 1

// shell errors
# define ERROR 1
# define MISUSE 2

// minishell errors
# define PIPE_ERROR 4
# define MEMORY_ERROR 5
# define SYNTAX_ERROR 6

// exec errors
# define IS_DIR 126
# define PERMISSION_DENIED 126
# define COMMAND_NOT_FOUND 127

// signals errors
# define EXIT_CTRL_C 130
# define EXIT_CTRL_BS 131

// text errors
# define QUOTES_ERROR "syntax error: quotes not closed\n"

#endif
