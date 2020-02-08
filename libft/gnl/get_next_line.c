/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscussel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:06:03 by bscussel          #+#    #+#             */
/*   Updated: 2019/11/01 21:57:56 by bscussel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void				bs_bufclr(char buffer[])
{
	size_t			i;

	i = 0;
	if (!buffer)
		return ;
	while (i < BUFF_SIZE + 1)
		buffer[i++] = '\0';
}

void				line_apply(char **line, char **str, int fd)
{
	int				i;
	int				len;
	char			*tmp;
	char			*cpy;

	i = 0;
	len = ft_strlen(str[fd]);
	tmp = ft_strnew(sizeof(char) * len);
	cpy = str[fd];
	while (*cpy != '\n' && *cpy != '\0')
		tmp[i++] = *cpy++;
	(*cpy == '\n') ? cpy++ : 0;
	str[fd] = ft_strcpy(str[fd], cpy);
	*line = ft_strdup(tmp);
	ft_strdel(&tmp);
}

int					get_next_line(const int fd, char **line)
{
	int				r;
	char			buffer[BUFF_SIZE + 1];
	static char		*str[255];
	char			*ptr;

	if (fd < 0 || line == NULL)
		return (-1);
	bs_bufclr(buffer);
	while ((r = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		ptr = str[fd];
		str[fd] = (!str[fd]) ? ft_strdup(buffer) : ft_strjoin(str[fd], buffer);
		bs_bufclr(buffer);
		ft_strdel(&ptr);
	}
	if (r <= -1 || (r == 0 && (!(ft_strlen(str[fd])))))
		return (r);
	line_apply(line, str, fd);
	return (1);
}
