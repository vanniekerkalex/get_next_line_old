/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-ni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:09:08 by avan-ni           #+#    #+#             */
/*   Updated: 2018/06/16 14:37:05 by avan-ni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_line(char *buf, char **l,
		const int fd, char *left[fd])
{
	int		size;
	char	*temp;

	while ((ft_delchr(buf, '\n') < 0) &&
			((size = read(fd, buf, BUFF_SIZE)) > 0))
	{
		buf[size] = '\0';
		temp = left[fd];
		left[fd] = ft_strjoin(temp, buf);
		ft_strdel(&temp);
	}
	if (size == -1)
		return (-1);
	ft_strdel(&buf);
	if (ft_delchr(left[fd], '\n') >= 0)
	{
		temp = left[fd];
		left[fd] = ft_strnew_delaft(temp, '\n');
		*l = ft_strnew_del(temp, '\n');
		ft_strdel(&temp);
		return (1);
	}
	*l = ft_strdup(left[fd]);
	ft_strdel(&left[fd]);
	return (ft_strlen(*l) > 0 ? 1 : 0);
}

int			get_next_line(const int fd, char **l)
{
	char		*buf;
	static char	*left[1001];

	buf = ft_strnew(BUFF_SIZE);
	if (fd < 0 || l == NULL || buf == NULL || BUFF_SIZE < 1)
		return (-1);
	if (left[fd] == NULL)
		left[fd] = ft_strnew(0);
	return (ft_read_line(buf, l, fd, left));
}
