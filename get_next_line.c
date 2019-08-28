/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssahai- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 13:41:25 by ssahai-           #+#    #+#             */
/*   Updated: 2019/08/16 15:07:14 by ssahai-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlenc(const char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] != c)
	{
		if (str[len] == '\0')
			return (len);
		len++;
	}
	return (len);
}

char	*ft_getline(char *str, char *buff, int fd)
{
	int		ret;
	char	*temp;

	ret = 1;
	while (!(ft_strchr(str, '\n')) && ret)
	{
		ret = read(fd, buff, BUFF_SIZE);
		if (ret < 0)
			return (NULL);
		if (ret)
		{
			buff[ret] = '\0';
			temp = str;
			if (!(str = ft_strjoin(str, buff)))
				return (NULL);
			free(temp);
		}
	}
	return (str);
}

char	*ft_stock(char *str)
{
	char	*next;
	char	*temp;
	int		i;

	i = 0;
	temp = str;
	while (temp[i] != '\n')
		if (!temp[i++])
			return (NULL);
	next = ft_strdup(&temp[i + 1]);
	free(temp);
	str = next;
	return (str);
}

int		get_next_line(const int fd, char **line)
{
	static char	*str = NULL;
	char		buff[BUFF_SIZE + 1];

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!str)
		str = ft_strnew(1);
	if (!(str = ft_getline(str, buff, fd)))
		return (-1);
	if (!(ft_strchr(str, '\n')) && str[0] != '\0')
	{
		*line = ft_strdup(str);
		ft_strdel(&str);
		return (1);
	}
	else if (ft_strchr(str, '\n'))
		*line = ft_strndup(str, ft_strlenc(str, '\n'));
	if (str[0] == '\0')
		return (0);
	str = ft_stock(str);
	return (1);
}
