/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:28:35 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/14 21:40:39 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	append_buffer(struct s_select *s, const char *str, int len)
{
	char	*new_str;

	new_str = ft_realloc(s->buf.str, s->buf.len + len);
	if (new_str == NULL)
		fatal_error("Memory allocation failed", s);
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

void	write_buffer(struct s_string buf)
{
	write(STDOUT_FILENO, buf.str, buf.len);
}
