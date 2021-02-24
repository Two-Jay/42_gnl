/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 01:44:31 by jekim             #+#    #+#             */
/*   Updated: 2021/02/24 13:17:18 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>

size_t	ft_strlen(char *str);
char	*ft_strchr(const char *src, char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strdup(char *s);
char	*ft_addback_str(char *s1, char *s2);
int		get_next_line(int fd, char **line);

#endif
