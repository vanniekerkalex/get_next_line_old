/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-ni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:09:08 by avan-ni           #+#    #+#             */
/*   Updated: 2018/06/08 16:06:44 by avan-ni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>

static int	ft_read_line(char *buf, char **l,
		const int fd, char *left[fd])
{
	int	size;
	char	*temp;
	
	while (((size = read (fd, buf, BUFF_SIZE)) >= 0) && (ft_delchr(left[fd], '\n') < 0))
	{
		buf[size] = '\0';
		temp = left[fd];
		ft_strdel(left[fd]);
		left[fd] = ft_strjoin(temp, buf);
		ft_strdel(&temp);
		ft_strdel(&buf);
	}
	if (size == 0)
	{
	       	if (ft_delchr(left[fd], '\n') < 0)
		{
			*l = ft_strdup(left[fd]);
			ft_strdel(left[fd]);
		} else
		{
			*l = ft_strnew_del(left[fd], '\n');
			 left[fd] = ft_strnew_delaft(ft_strjoin(temp, buf), '\n');
		}
		return (1);
	}
	*l = *l = ft_strnew_del(left[fd], '\n');


}

int			get_next_line(const int fd, char **l)
{
	char		*buf;
	int		size;
	int		res;
	static char	*left[1001];
	
	buf = ft_strnew(BUFF_SIZE);
	if (fd < 0 || l == NULL || buf == NULL || BUFF_SIZE < 1)
		return (-1);
	if (left[fd] == NULL)
		left[fd] = ft_strnew(0);
	
	return (ft_read_line(buf, l, fd, left));

}
