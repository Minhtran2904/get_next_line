/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitran <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:42:54 by mitran            #+#    #+#             */
/*   Updated: 2022/11/18 10:21:13 by mitran           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_line(char **line)
{
	free(*line);
	return (NULL);
}

static void	update_buff(char *s1, char *s2)
{
	int	index;

	index = 0;
	while (s2[index])
	{
		s1[index] = s2[index];
		index++;
	}
	s1[index] = '\0';
}

static int	is_line(char *buff, char **line)
{
	char	*storage;
	int		new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	new_line = 0;
	if (buff[i] == '\n')
		new_line = 1;
	storage = ft_calloc(new_line + i + 1, 1);
	if (storage == NULL)
		return (NO_LINE);
	while (j < new_line + i)
	{	
		storage[j] = buff[j];
		j++;
	}
	*line = join_n_free(*line, storage);
	if (line == NULL)
		return (NO_LINE);
	update_buff(buff, &buff[new_line + i]);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	int			count;
	int			new_line;

	line = NULL;
	new_line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (new_line == 0)
	{
		new_line = is_line(buff, &line);
		if (new_line == NO_LINE)
			return (free_line(&line));
		if (new_line == YES_LINE)
		{
			count = read(fd, buff, BUFFER_SIZE);
			if (count == 0 && *line)
				new_line = 1;
			else if (count <= 0)
				return (free_line(&line));
			buff[count] = '\0';
		}
	}
	return (line);
}
