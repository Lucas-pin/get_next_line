/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:05:06 by lpin              #+#    #+#             */
/*   Updated: 2023/11/17 13:46:53 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

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

void	ft_resize(t_body *body, char *buffer)
{
	char	*temp;

	if (!body || !buffer)
		return ;
	body->content_size = ft_strlen(body->content);
	temp = malloc(body->content_size + 1);
	if (temp == NULL)
	{
		ft_destroyer(temp);
		return ;
	}
	ft_strlcat(temp, body->content, (body->content_size + 1));
	ft_destroyer(body->content);
	body->content = malloc(body->content_size + body->buffer_size + 1);
	if (body->content == NULL)
	{
		ft_destroyer(body->content);
		return ;
	}
	ft_strlcat(body->content, temp, \
	(body->content_size + body->buffer_size + 1));
	ft_strlcat(body->content, buffer, \
					(body->content_size + body->buffer_size + 1));
	ft_destroyer(temp);
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
		ft_strlcat(body->content, buffer, (body->buffer_size + 1));
	}
	else
		ft_resize(body, buffer);
}

void	ft_last_read(t_body *body)
{
	if (ft_searcher(body->content) == -1)
	{
		body->ret = malloc (ft_strlen(body->content) + 2);
		if (body->ret == NULL)
		{
			ft_destroyer(body->ret);
			return ;
		}
		ft_strlcat(body->ret, body->content, (ft_strlen(body->content) + 2));
		ft_strlcat(body->ret, "\n", (ft_strlen(body->content) + 2));
		ft_destroyer(body->content);
		body->content = NULL;
	}
	if (ft_searcher(body->content) > 0)
	{
		body->ret = malloc (ft_searcher(body->content) + 1);
		if (body->ret == NULL)
		{
			ft_destroyer(body->ret);
			return ;
		}
		ft_strlcat(body->ret, body->content, (ft_searcher(body->content) + 1));
		if (ft_searcher(body->content) == 0)
		{
			ft_destroyer(body->content);
			body->content = NULL;
		}
		else
			ft_put_forward(body->content, ft_searcher(body->content));
	}
}

char	*get_next_line(int fd)
{
	static t_body	body = {0, 0, 0, 0, NULL, NULL};
	char			buffer[BUFFER_SIZE];
	int				i;
	int				searcher_flag;
	int				read_flag;

	searcher_flag = 0;
	body.fd = fd;
	if (body.fd == -1)
	{
		ft_destroyer(body.content);
		ft_destroyer(body.ret);
		body.content = NULL;
		body.ret = NULL;
		return (NULL);
	}
	while (searcher_flag <= 0)
	{
		i = sizeof(buffer);
		while (i >= 0)
		{
			buffer[i] = '\0';
			--i;
		}
		read_flag = read(body.fd, buffer, sizeof(buffer));
		if (read_flag == -1)
		{
			ft_destroyer(body.content);
			ft_destroyer(body.ret);
			body.content = NULL;
			body.ret = NULL;
			return (NULL);
		}
		else if (read_flag == 0)
			break ;
		body.buffer_size = ft_strlen(buffer);
		ft_read(&body, buffer);
		searcher_flag = ft_searcher(body.content);
	}
	if (read_flag == 0)
		ft_last_read(&body);
	else
	{
		body.ret = malloc (ft_searcher(body.content) + 1);
		if (body.ret == NULL)
			return (ft_destroyer(body.ret));
		if (body.fd == -1)
		{
			ft_destroyer(body.content);
			ft_destroyer(body.ret);
			body.content = NULL;
			body.ret = NULL;
			return (NULL);
		}
		ft_strlcat(body.ret, body.content, ft_searcher(body.content) + 1);
		ft_put_forward(body.content, ft_searcher(body.content));
		if (ft_searcher(body.content) == 0)
		{
			ft_destroyer(body.content);
			body.content = NULL;
		}
	}
	if (ft_strlen(body.ret) == 0)
		body.ret = NULL;
	return (body.ret);
}
