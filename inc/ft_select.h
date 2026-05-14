/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:15:42 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/14 21:32:08 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

/* INCLUDES */

# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <errno.h>
# include <sys/ioctl.h>

/* STRUCTURES */

typedef struct s_string
{
	char	*str;
	int		len;
}	t_string;

typedef struct s_select
{
	struct termios	orig_termios;
	struct winsize	win_size;
	struct s_string	buf;

}	t_select;

/* ENUMERATIONS */

enum e_key
{
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_ENTER,
	KEY_ESC = 27,
	KEY_BACKSPACE,
	KEY_DELETE,
	KEY_UNKNOWN
};

/* PROTOTYPES */

// conf.c
void	enable_raw_mode(struct s_select *s);
void	disable_raw_mode(struct s_select *s);
int		get_window_size(struct s_select *s);

// keys.c
int		ctrl_key(const int k);
char	editor_read_key(struct s_select *s);

// render.c
void	editor_process_keypress(struct s_select *s);
void	editor_refresh_screen(void);
void	editor_draw_arguments(char **args, int count, struct s_select *s);

// buffer.c
void	append_buffer(struct s_select *s, const char *str, int len);
void	write_buffer(struct s_string buf);
void	clear_buffer(struct s_select *s);

void	fatal_error(const char *msg, struct s_select *s);

#endif