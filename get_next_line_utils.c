/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 03:50:41 by jekim             #+#    #+#             */
/*   Updated: 2021/02/19 14:27:12 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	char *temp;
	
	temp = str;
	while (*temp++)
		;
	return (size_t)(temp - str - 1);
}

char	*ft_strchr(const char *src , char c)
{
	while (*src && *src != c)
		src++;
	if (*src == c)
		return ((char *)src);
	return (NULL);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *d;
	unsigned char *s;
	
	if (!dst && !src)
		return (NULL);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n--)
		*(d++) = *(s++);
	return (dst);
}

char	*ft_strdup(char *s)
{
	char	*ret;
	int		len;

	len = (int)ft_strlen(s);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s, (len + 1));
	return (ret);
}


char	*ft_addback_str(char *s1, char *s2)
{
	char *ret;
	size_t s1_l;
	size_t s2_l;

	if (!s1 && !s2)
		return (0);
	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	ret = malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (!ret)
		return (NULL);
	while (*s1)
		*(ret++) = *(s1++);
	while (*s2)
		*(ret++) = *(s2++);
	*ret = '\0';
	return (ret);
}
