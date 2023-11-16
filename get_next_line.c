/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:05:06 by lpin              #+#    #+#             */
/*   Updated: 2023/11/16 11:54:16 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_put_forward(char *src, int len)
{
	int		i;
	char	*temp;

	i = ft_strlen(src);
	temp = src;
	if (!src || len == 0 || len == -1)
		return (src);
	while (i >= len)
	{
		*src = *(src + len);
		--i;
		src++;
	}
	while (*src)
	{
		*src = '\0';
		src++;
	}
	return (temp);
}

void	ft_read(t_body *body, char *buffer)
{
	if (body->content == NULL)
	{
		body->content = malloc((sizeof(char) * (body->buffer_size + 1)));
		if (body->content == NULL)
		{
			ft_destroyer(body->content);
			return ;
		}
	}
	ft_strlcat(body->content, buffer, (body->buffer_size + 1));
}

char	*get_next_line(int fd)
{
	static t_body	body = {0, 0, 0, 0, NULL, NULL};
	char			buffer[18];
	int				i;

	while (ft_searcher(body.content) <= 0)
	{
		i = sizeof(buffer);
		while (i >= 0)
		{
			buffer[i] = '\0';
			--i;
		}
		if (read(fd, buffer, sizeof(buffer)) == -1)
			return (NULL);
		if (ft_strlen(buffer) > sizeof(buffer))
			body.buffer_size = sizeof(buffer);
		else
			body.buffer_size = ft_strlen(buffer);
		ft_read(&body, buffer);
	}
	body.ret = malloc (ft_searcher(body.content) + 1);
	ft_strlcat(body.ret, body.content, ft_searcher(body.content) + 1);
	ft_put_forward(body.content, ft_searcher(body.content));
	printf("El body.content es: %s", body.content);
	return (body.ret);
}

int	main(void)
{
	int		fd;
	char	*ret;

	fd = open("prueba.txt", O_RDONLY);
	ret = get_next_line(fd);
	printf("El ret es: %s", ret);
	return (0);
}
