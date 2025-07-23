#include "get_next_line.h"

// char *get_remain(char *s, int c)
// {
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	i = 0;
// 	while (s[i])
// 	{
// 		if ((unsigned char)s[i] == (unsigned char)c)
// 			return ((char *)s + i + 1);
// 		i++;
// 	}
// 	if ((unsigned char)s[i] == (unsigned char)c)
// 		return ((char *)s + i);
// 	return (NULL);
// }

// char *get_new_line(char *s)
// {
// 	int len;
// 	int i;
// 	char *line;

// 	len = 0;
// 	i = 0;
// 	while (s[len] && s[len] != '\n')
// 		len++;
// 	line = malloc(sizeof(char) * (len + 1));
// 	if (!line)
// 		return (perror("Error"), NULL);
// 	while (i < len)
// 	{
// 		line[i] = s[i];
// 		i++;
// 	}
// 	line[i] = '\0';
// 	return (line);
// }

char *get_line_and_remain(char **remain)
{
	size_t i;
	char *line;
	char *new_remain;

	i = 0;
	if (!ft_strchr((*remain), '\n'))
		return (NULL);
	while ((*remain)[i] != '\n')
		i++;
	line = ft_strndup((*remain), i + 1);
	new_remain = ft_strndup((*remain) + i + 1, ft_strlen(*remain) - i - 1);
	free(*remain);
	*remain = new_remain;
	return (line);
}

char	*get_next_line(int fd)
{
	static char *remain;
	ssize_t read_res;
	char buf[BUF_SIZE + 1];
	char *tmp;
	char *line;
	
	if(!remain)
	{
		remain = malloc(1);
		if (!remain)
			return (NULL);
		remain[0] = '\0';
	}
	else if (ft_strchr(remain, '\n'))
	{
		line = get_line_and_remain(&remain);
		return (line);
	}
	read_res = read(fd, buf, BUF_SIZE);
	if (read_res < 0)
		return (perror("Error"), NULL);
	while (read_res > 0)
	{
		buf[read_res] = '\0';
		tmp = ft_strjoin(remain, buf);
		free(remain);
		remain = tmp;
		if (ft_strchr(remain, '\n'))
			break ;
		read_res = read(fd, buf, BUF_SIZE);
	}
	// if (read_res == 0 && !ft_strchr(remain, '\n'))
	// 	return (remain);
	printf("\nWhat we've got : %s", remain);
	line = get_line_and_remain(&remain);
	printf("\nLine : %s", line);
	printf("\nNew remain : %s", remain);
	return (line);
}

int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (perror("Error"), 1);
	line = get_next_line(fd);
	// printf("\nFirst line : %s", line);
	free(line);
	line = get_next_line(fd);
	free(line);
	// printf("\nSecond line : %s", line);
	line = get_next_line(fd);
	free(line);
	// printf("\nThird line : %s", line);
	close(fd);
	return (0);
}