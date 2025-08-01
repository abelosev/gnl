/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:01:51 by anbelose          #+#    #+#             */
/*   Updated: 2025/08/01 14:27:55 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line_remain_outil(char **remain, int i)
{
	char	*new_remain;
	char	*line;

	line = ft_strndup(*remain, i + 1);
	if (!line)
	{
		free(*remain);
		*remain = NULL;
		return (NULL);
	}
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

char	*get_line_and_remain(char **remain)
{
	size_t	i;
	char	*line;

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
	if (!line)
	{
		free(*remain);
		*remain = NULL;
	}
	return (line);
}

void	reading(int fd, char **remain)
{
	ssize_t	read_res;
	char	*buf;
	char	*tmp;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return ;
	read_res = read(fd, buf, BUFFER_SIZE);
	if (read_res < 0)
	{
		free(*remain);
		*remain = NULL;
		return (free(buf));
	}
	while (read_res > 0)
	{
		buf[read_res] = '\0';
		tmp = ft_strjoin(*remain, buf);
		free(*remain);
		*remain = tmp;
		if (!tmp)
			return (free(buf));
		if (ft_strchr(*remain, '\n'))
			break ;
		read_res = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (!remain)
	{
		remain = malloc(1);
		if (!remain)
			return (NULL);
		remain[0] = '\0';
	}
	if (!ft_strchr(remain, '\n'))
		reading(fd, &remain);
	line = get_line_and_remain(&remain);
	if (!line && remain)
	{
		free(remain);
		remain = NULL;
	}
	return (line);
}
