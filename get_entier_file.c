#include "gnl.h"

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	if (!src || !dst)
		return (0);
	i = 0;
	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (size <= d_len)
		return (s_len + size); //??
	while ((i < size - d_len - 1) && src[i])
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}

size_t file_len_count(void)
{
	int fd;
	size_t file_len = 0;
	ssize_t read_res;
	char buf[1];

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (perror("Error"), 1);
	read_res = read(fd, buf, 1);
	if (read_res < 0)
		return (perror("Error"), -1);
	while (read_res == 1)
	{
		file_len++;
		read_res = read(fd, buf, 1);
	}
	close(fd);
	return (file_len);
}

char	*get_next_line(int fd)
{
	ssize_t read_res;
	char buf[BUF_SIZE + 1];
	char *res;
	size_t file_len;

	file_len = file_len_count();
	// printf("%zu\n", file_len);

	res = malloc(sizeof(char) * (file_len + 1));
	if (!res)
		return (perror("Error"), NULL);
	res[0] = '\0';

	read_res = read(fd, buf, BUF_SIZE);
	if (read_res < 0)
		return (perror("Error"), NULL);
	while (read_res > 0)
	{
		buf[read_res] = '\0';
		ft_strlcat(res, buf, file_len + 1);
		buf[0] = '\0';
		read_res = read(fd, buf, BUF_SIZE);
	}
	return (res);
}

int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (perror("Error"), 1);
	line = get_next_line(fd);
	if (!line)
		return(perror("Error"), 1);
	printf("%s\n", line);
	close(fd);
	return (0);
}