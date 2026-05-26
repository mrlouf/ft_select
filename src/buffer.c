/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:28:35 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/26 10:52:00 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void	append_buffer(struct s_select *s, const char *str, int len)
{
	char	*new_str;

	new_str = ft_realloc(s->buf.str, s->buf.len, s->buf.len + len);
	if (new_str == NULL)
		fatal_error("Memory allocation failed while appending to buffer");
	ft_memcpy(new_str + s->buf.len, str, len);
	s->buf.str = new_str;
	s->buf.len += len;
}

void	clear_buffer(struct s_select *s)
{
	free(s->buf.str);
	s->buf.str = NULL;
	s->buf.len = 0;
}

void	write_buffer(int fd, struct s_string buf)
{
	write(fd, buf.str, buf.len);
}
