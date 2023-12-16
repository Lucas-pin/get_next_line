/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mian.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 10:28:51 by lpin              #+#    #+#             */
/*   Updated: 2023/11/17 13:46:56 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("prueba.txt", O_RDONLY);
	while ((line = get_next_line(-1)))
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}