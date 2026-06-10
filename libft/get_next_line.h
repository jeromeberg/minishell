#ifndef GET_NEXT_LINE_H

#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_read_and_fill(int fd, char *stash);
char	*ft_extract_line(char *stash);
char	*ft_update_stash(char *old);
char	*ft_str_join_gnl(char *s1, char *s2);
char	*ft_strcpy_nl(char *dest, char *src, int nl_found);
int		ft_nl_found(char *s, char c);

#endif
