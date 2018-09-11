/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 09:21:46 by dshumba           #+#    #+#             */
/*   Updated: 2018/07/01 16:10:28 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "libft.h"

int					ft_new_line(char **s, char **line, int fd, int ret)
{
	char			*tmp;
	int				len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		*line = ft_strsub(s[fd], 0, len);
		tmp = ft_strdup(s[fd] + len + 1);
		free(s[fd]);
		s[fd] = tmp;
		if (s[fd][0] == '\0')
			ft_strdel(&s[fd]);
	}
	else if (s[fd][len] == '\0')
	{
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
		if (ret == BUFF_SIZE)
			return (0);
	}
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	static char		*s[255];
	char			buf[BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strnew(1);
		tmp = ft_strjoin(s[fd], buf);
		free(s[fd]);
		s[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (s[fd] == NULL || s[fd][0] == '\0'))
		return (0);
	return (ft_new_line(s, line, fd, ret));
}
*/

#include "libft.h"

static char	*readtobuf(const int fd, char *buf, int *ret)
{
	char	buffer[BUFF_SIZE + 1];
	char	*store;

	store = buf;
	*ret = read(fd, buffer, BUFF_SIZE);
	buffer[*ret] = '\0';
	if (!(buf = ft_strjoin(store, buffer)))
		return (0);
	ft_strdel(&store);
	store = NULL;
	return (buf);
}

int			cleanbuf(char **buf)
{
	ft_bzero(*buf, ft_strlen(*buf));
	return (-1);
}

int			put_end(char **line, char **buf)
{
	if (!(*line = ft_strdup(*buf)))
		return (cleanbuf(buf));
	cleanbuf(buf);
	return (1);
}

int			cacheline(char **line, char *buf)
{
	char	*str;
	char	*charstr;

	if ((str = ft_strchr(buf, '\n')) != NULL)
	{
		*str = '\0';
		*line = ft_strnew(ft_strlen(buf));
		charstr = *line;
		if (!(*line = ft_strdup(buf)))
			return (cleanbuf(&buf));
		ft_memmove(buf, str + 1, ft_strlen(str + 1) + 1);
		free(charstr);
		return (1);
	}
	return (0);
}

int			get_next_line(int const fd, char **line)
{
	static char	*buf;
	int			ret;

	ret = 1;
	if (buf == NULL)
		buf = ft_strnew(0);
	if (!line || fd < 0)
		return (cleanbuf(&buf));
	while (ret > 0)
	{
		ret = cacheline(line, buf);
		if (ret != 0)
			return (ret);
		if (!(buf = readtobuf(fd, buf, &ret)))
			return (cleanbuf(&buf));
	}
	if (ret == 0 && ft_strlen(buf))
		ret = put_end(&(*line), &buf);
	cleanbuf(&buf);
	return (ret);
}