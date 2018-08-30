/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshumba <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 10:35:09 by dshumba           #+#    #+#             */
/*   Updated: 2018/08/27 13:49:26 by dshumba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracer.h"

void		read_file(char *argv)
{
	int fd;
	int ret;	
	char **line = NULL;


	fd = open(argv, O_RDONLY);
	while ((ret = get_next_line(fd, line) > 0) == 0)
		ft_putstr(*line);
}
