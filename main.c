#include "get_next_line.h"

int main()
{
	char *line;
	int fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[%s]", line);
		free(line);
	}
	return (0);
}
