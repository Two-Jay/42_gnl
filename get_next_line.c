/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:44:15 by jekim             #+#    #+#             */
/*   Updated: 2021/02/19 14:02:26 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_get_current_line(int fd, t_struct *storage, char **line)
{
	printf("get_curline entered =====================\n");
	char *temp;

	if (*(storage[fd].lon) == '\n')
	{
		printf("storage backup : %s\n", storage[fd].backup);
		*(storage[fd].lon) = '\0';
		temp = storage[fd].backup;
		*line = ft_strdup(storage[fd].backup);
		storage[fd].backup = ft_strdup(storage[fd].lon + 1);
		free(temp);
		temp = 0;
		return (1);
	}
	else if (*(storage[fd].lon) == '\0')
	{
		*line = ft_strdup(storage[fd].backup);
		free(storage[fd].backup);
		storage[fd].backup = 0;
		storage[fd].lon = 0;
		return (0);
	}
	else
		return (-1);
}

static int	ft_read_buf(int fd, t_struct *storage)
{
	int read_l;
	char *buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	read_l = BUFFER_SIZE;
	while (read_l && read_l == BUFFER_SIZE)
	{
		read_l = read(fd, buf, BUFFER_SIZE);
		if (read_l < 0)
			break ;
		buf[read_l] = '\0';
		storage[fd].backup = ft_addback_str(storage[fd].backup, buf);
		storage[fd].lon = ft_strchr(storage[fd].backup, '\n');
		if (storage[fd].lon || read_l != BUFFER_SIZE)
			break ;
	}
	printf("== BUFFER CHECK - %s\n", storage[fd].backup);
	if (read_l < 0)
		return (-1);
	return (1);
	// the buffer fries away as while loop is finished with SEGF
}

int			get_next_line(int fd, char **line)
{
	static t_struct	storage[OPEN_MAX];
	int				read_check;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || !line)
		return (-1);
	read_check = 0;
	if (!storage[fd].backup)
		storage[fd].backup = ft_strdup("");
	read_check = ft_read_buf(fd, storage);
	if (read_check == -1)
		return (-1);
	if (!storage[fd].lon && !(ft_strchr(storage[fd].backup, '\n')))
		storage[fd].lon += ((int)ft_strlen(storage[fd].backup) + 1);
	return (ft_get_current_line(fd, storage, line));
}
