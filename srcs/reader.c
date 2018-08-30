/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdorner <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 06:42:41 by jdorner           #+#    #+#             */
/*   Updated: 2018/08/06 11:19:08 by jdorner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void        ft_lstrev(t_list **alst)
{
    t_list    *prev;
    t_list    *cur;
    t_list    *next;

    prev = NULL;
    cur = *alst;
    while (cur != NULL)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    *alst = prev;
}

t_list	*read_to_list_arg(int argc, char **argv, t_list *ret)
{
	int		fd;
	char	*line;

	ret = NULL;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd > 0)
		{
			line = NULL;
			while ((get_next_line(fd, &line)) > 0)
			{
				ft_strcat(line, "\n");
				ft_lstadd(&ret, ft_lstnew(line, ft_strlen(line) + 1));
				ft_strdel(&line);
			}
		}
	}
	if (ret != NULL)
		close(fd);
	return (ret);
}

t_list	*read_file_arg(int argc, char **argv)
{
	t_list		*ret;

	ret = NULL;
	if (!(ret = read_to_list_arg(argc, argv, ret)))
		return (NULL);
	return (ret);
}

t_list	*read_to_list(char *path, t_list *ret)
{
	int		fd;
	char	*line;

	ret = NULL;
	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		line = NULL;
		while ((get_next_line(fd, &line)) > 0)
		{
			ft_strcat(line, "\n");
			ft_lstadd(&ret, ft_lstnew(line, ft_strlen(line) + 1));
			ft_strdel(&line);
		}
	}
	ft_lstrev(&ret);
	if (ret != NULL)
		close(fd);
	return (ret);
}

t_list	*read_file(char *path)
{
	t_list		*ret;

	ret = NULL;
	if (!(ret = read_to_list(path, ret)))
		return (NULL);
	return (ret);
}
