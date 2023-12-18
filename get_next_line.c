/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:05:06 by lpin              #+#    #+#             */
/*   Updated: 2023/12/16 18:02:27 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

int	ft_read(t_body *body, char *buffer)
{
	body->read_size = 1;
	body->offset = 0;
	while (body->offset == 0 && body->read_size > 0)
	{
		buffer[BUFFER_SIZE] = '\0';
		body->read_size = read(body->fd, buffer, BUFFER_SIZE);
		if (body->read_size > 0)
			ft_save_content(body, buffer);
		body->offset = ft_searcher(body->content);
	}
	if (body->read_size == 0 && body->offset == -1)
		return (1);
	else if (body->read_size == -1)
		return (-1);
	else
		return (0);
}

void	ft_resize(t_body *body, char *buffer)
{
	char	*temp;

	body->content_size = ft_strlen(body->content, -1) + body->read_size;
	temp = malloc(sizeof(char) * (ft_strlen(body->content, -1) + 1));
	if (temp == NULL)
		return ;
	ft_strlen(temp, ft_strlen(body->content, -1));
	ft_strlcat(temp, body->content, (ft_strlen(body->content, -1) + 1));
	ft_destroyer(&body->content);
	body->content = malloc(sizeof(char) * (body->content_size + 1));
	if (body->content == NULL)
		return ;
	ft_strlen(body->content, body->content_size);
	ft_strlcat(body->content, temp, ft_strlen(temp, -1) + 1);
	ft_strlcat(body->content, buffer, body->content_size + 1);
	ft_destroyer(&temp);
}

void	ft_save_ret(t_body *body)
{
	if (body->content == NULL)
	{
		body->ret = NULL;
		return ;
	}
	if (body->offset == 0)
	{
		body->ret = malloc (sizeof(char) * ft_strlen(body->content, -1) + 1);
		if (body->ret == NULL)
			return ;
		ft_strlen(body->ret, ft_strlen(body->content, -1));
		ft_strlcat(body->ret, body->content,
			(ft_strlen(body->content, -1) + 1));
		ft_put_forward(body->content, (ft_strlen(body->content, -1) + 1));
	}
	else if (body->offset != 0)
	{
		body->ret = malloc (sizeof(char) * body->offset + 1);
		if (body->ret == NULL)
			return ;
		ft_strlen(body->ret, body->offset);
		ft_strlcat(body->ret, body->content, (body->offset + 1));
		ft_put_forward(body->content, body->offset);
	}
	body->offset = ft_searcher(body->content);
}

void	ft_save_content(t_body *body, char *buffer)
{
	if (*buffer == '\0')
		return ;
	if (body->content == NULL)
	{
		body->content = malloc((body->read_size + 1));
		if (body->content == NULL)
			return ;
		ft_strlen(body->content, body->read_size);
		ft_strlcat(body->content, buffer, (body->read_size + 1));
	}
	else
		ft_resize(body, buffer);
}

char	*get_next_line(int fd)
{
	static t_body	body = {0, 0, 0, 0, NULL, NULL};
	char			buffer[BUFFER_SIZE + 1];
	int				read_ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	body.fd = fd;
	read_ret = 0;
	ft_strlen(buffer, BUFFER_SIZE);
	if (ft_searcher(body.content) <= 0)
		read_ret = ft_read(&body, buffer);
	if (read_ret == 0)
	{
		ft_save_ret(&body);
		if (ft_strlen(body.content, -1) == 0)
			ft_destroyer(&body.content);
	}
	else if (read_ret == -1)
		body.ret = ft_destroyer(&body.content);
	else if (read_ret == 1)
		body.ret = ft_destroyer(&body.content);
	return (body.ret);
}
