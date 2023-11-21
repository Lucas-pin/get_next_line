/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin < lpin@student.42malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:40:50 by lpin              #+#    #+#             */
/*   Updated: 2023/11/17 13:47:00 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_searcher(const char *haystack)
{
	int		offset;
	char	*temp;

	offset = 0;
	temp = (char *)haystack;
	if (!haystack)
		return (0);
	while (*temp && *temp != '\n')
	{
		++offset;
		temp++;
	}
	if (*temp == '\n')
		return (offset + 1);
	else
		return (-1);
}

void	ft_init(t_body *body)
{
	body->fd = 0;
	body->content_size = 0;
	body->offset = 0;
}

unsigned int	ft_strlen(const char *s)
{
	unsigned int	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (s[len])
		len++;
	return (len);
}

unsigned int	ft_strlcat(char *dst, const char *src, unsigned int dstsize)
{
	unsigned int	dst_len;
	unsigned int	src_len;
	unsigned int	i;
	unsigned int	j;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	j = 0;
	if (src == NULL || dstsize == 0)
		return (0);
	if (dstsize > 0 && dst_len < dstsize)
	{
		while (dst[i] != '\0')
			++i;
		while (src[j] != '\0' && j < (dstsize - dst_len - 1))
		{
			dst[i] = src[j];
			++i;
			++j;
		}
		dst[i] = '\0';
		return (dst_len + src_len);
	}
	return (src_len + dstsize);
}

void	*ft_destroyer(char *to_destroy)
{
	char	*temp;

	temp = to_destroy;
	if (!temp)
		return (NULL);
	while (*temp)
	{
		*temp = '\0';
		temp++;
	}
	free(to_destroy);
	return (NULL);
}
