/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:44:53 by lpin              #+#    #+#             */
/*   Updated: 2023/11/03 22:42:01 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_body
{
	int				fd;
	unsigned int	content_size;
	unsigned int	offset;
	char			*content;
	char			*ret;
}					t_body;

int				ft_searcher(const char *haystack);

void			ft_init(t_body **body);

unsigned int	ft_strlen(const char *s);

unsigned int	ft_strlcat(char *dst, const char *src, unsigned int dstsize);

void			ft_destroyer(char *to_destroy);

#endif