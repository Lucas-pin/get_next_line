/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:05:06 by lpin              #+#    #+#             */
/*   Updated: 2023/11/08 19:16:20 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*ft_put_forward(char *src, int len)
{
	int	i;

	i = len;
	if (!src || len == 0 || len == -1)
		return (src);
	while (i > 0)
	{
		*src = *(src + len);
		--i;
		src++;
	}
	return (src);
}

char	*get_next_line(int fd)
{
	static t_body	body = {0, 0, 0, NULL, NULL};
	char			buffer[1000];

	read(fd, buffer, sizeof(buffer));
	body.offset = ft_searcher(buffer);
	body.content = buffer;
	return (body.ret);
}

int	main(void)
{
	int	fd;

	fd = open("prueba.txt", O_RDONLY);
	get_next_line(fd);
	return (0);
}
