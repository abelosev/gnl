#include "get_next_line.h"

char *get_line_remain_outil(char **remain, int i)
{
	char *new_remain;
	char *line;

	line = ft_strndup(*remain, i + 1);
	if (!line)
		return (free(*remain), NULL);
	new_remain = ft_strndup((*remain) + i + 1, ft_strlen(*remain) - i - 1);
	if (!new_remain)
	{
		free(*remain);
		free(line);
		*remain = NULL;
		return (NULL);
	}
	free(*remain);
	*remain = new_remain;
	return (line);
}

char *get_line_and_remain(char **remain)
{
	size_t i;
	char *line;

	i = 0;
	if (!*remain || !**remain)
		return (NULL);
	if (!ft_strchr((*remain), '\n'))
	{
		line = ft_strndup(*remain, ft_strlen(*remain));
		free(*remain);
		*remain = NULL;
		return (line);
	}
	while ((*remain)[i] != '\n')
		i++;
	line = get_line_remain_outil(remain, i);
	return (line);
}

void reading(int fd, char **remain)
{
	ssize_t read_res;
	char buf[BUF_SIZE + 1];
	char *tmp;

	read_res = read(fd, buf, BUF_SIZE);
	if (read_res < 0)
		return ;
	while (read_res > 0)
	{
		buf[read_res] = '\0';
		tmp = ft_strjoin(*remain, buf);
		if (!tmp)
		{
			free(*remain);
			*remain = NULL;
			return ;
		}
		free(*remain);
		*remain = tmp;
		if (ft_strchr(*remain, '\n'))
			break ;
		read_res = read(fd, buf, BUF_SIZE);
	}
}

char	*get_next_line(int fd)
{
	static char *remain;
	char *line;

	if (BUF_SIZE <= 0 || fd < 0)
		return (NULL);
	if(!remain)
	{
		remain = malloc(1);
		if (!remain)
			return (NULL);
		remain[0] = '\0';
	}
	if (!ft_strchr(remain, '\n'))
		reading(fd, &remain);
	line = get_line_and_remain(&remain);
	return (line);
}