/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:44:15 by jekim             #+#    #+#             */
/*   Updated: 2021/02/24 13:54:21 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free_queue(int fd, char **queue)
{
	free(queue[fd]);
	queue[fd] = 0;
	return (NULL);
}

static int	ft_dequeue_text(int fd, char *lon, char **queue, char **line)
{
	char *tmp_ptr;

	tmp_ptr = 0;
	if (*lon == '\n')
	{
		*lon = '\0';
		tmp_ptr = queue[fd];
		*line = ft_strdup(queue[fd]);
		queue[fd] = ft_strdup(lon + 1);
		free(tmp_ptr);
		tmp_ptr = 0;
		return (1);
	}
	else if (*lon == '\0')
	{
		*line = ft_strdup(queue[fd]);
		ft_free_queue(fd, queue);
		return (0);
	}
	else
		return (-1);
}

static char	*ft_enqueue_text(int fd, char **queue)
{
	int		read_byte;
	char	*buf;
	char	*n_ptr;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	n_ptr = 0;
	read_byte = BUFFER_SIZE;
	while (!n_ptr && read_byte == BUFFER_SIZE)
	{
		read_byte = read(fd, buf, BUFFER_SIZE);
		if (read_byte <= 0)
			break ;
		buf[read_byte] = '\0';
		queue[fd] = ft_addback_str(queue[fd], buf);
		n_ptr = ft_strchr(queue[fd], '\n');
	}
	free(buf);
	if (read_byte < 0)
		ft_free_queue(fd, queue);
	if (!n_ptr)
		n_ptr = (queue[fd] + ft_strlen(queue[fd]));
	return (n_ptr);
}

int			get_next_line(int fd, char **line)
{
	static char	*queue[OPEN_MAX];
	char		*lon;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	if (!queue[fd])
		queue[fd] = ft_strdup("");
	else if (queue[fd] && ft_strchr(queue[fd], '\n'))
	{
		lon = ft_strchr(queue[fd], '\n');
		return (ft_dequeue_text(fd, lon, queue, line));
	}
	lon = ft_enqueue_text(fd, queue);
	if (!lon)
		return (-1);
	return (ft_dequeue_text(fd, lon, queue, line));
}
