#include "get_next_line.h"

char	*ft_read_and_fill(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(sizeof (char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read && !ft_nl_found(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		stash = ft_str_join_gnl(stash, buffer);
	}
	free(buffer);
	return (stash);
}

char	*ft_extract_line(char *stash)
{
	char	*line;
	size_t	len;
	size_t	i;

	i = 0;
	if (stash[0] == 0)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	len = i + (stash[i] == '\n');
	line = malloc(sizeof (char) * (len + 1));
	if (!line)
		return (NULL);
	line = ft_strcpy_nl(line, stash, 1);
	return (line);
}

char	*ft_update_stash(char *old)
{
	char	*stash;
	int		start;

	start = 0;
	while (old[start] && old[start] != '\n')
		start++;
	if (old[start] == 0)
	{
		free (old);
		return (NULL);
	}
	stash = malloc(sizeof (char) * (ft_strlen(old + start) + 1));
	if (!stash)
		return (NULL);
	stash = ft_strcpy_nl(stash, old + start + 1, 0);
	free(old);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*extracted_line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_read_and_fill(fd, stash);
	if (!stash)
		return (NULL);
	extracted_line = ft_extract_line(stash);
	stash = ft_update_stash(stash);
	return (extracted_line);
}
