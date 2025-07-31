#include "get_next_line.h"

int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (perror("Error"), 1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("\nLine : [%s]", line);
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}