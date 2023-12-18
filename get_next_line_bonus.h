/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpin <lpin@student.42.malaga.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:44:53 by lpin              #+#    #+#             */
/*   Updated: 2023/12/18 20:13:37 by lpin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>

typedef struct s_body
{
	int				fd;
	int				read_size;
	unsigned int	content_size;
	int				offset;
	char			*content;
	char			*ret;
}					t_body;

int				ft_searcher(const char *haystack);

unsigned int	ft_strlen(char *s, int i);

unsigned int	ft_strlcat(char *dst, char *src, unsigned int dstsize);

void			*ft_destroyer(char **to_destroy);

char			*ft_put_forward(char *src, int len);

void			ft_save_content(t_body *body, char *buffer);

int				ft_read(t_body *body, char *buffer);

void			ft_resize(t_body *body, char *buffer);

void			ft_save_ret(t_body *body);

char			*get_next_line(int fd);

#endif