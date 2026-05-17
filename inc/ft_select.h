/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:15:42 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/17 16:41:30 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

/* INCLUDES */

# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <termcap.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <signal.h>

# include <stdio.h>

/* STRUCTURES */

typedef struct s_string
{
	char	*str;
	int		len;
}	t_string;

typedef struct s_cursor
{
	int	x;
	int	y;
}	t_cursor;

typedef struct s_termcaps
{
    char    *cm;
    char    *cl;
    char    *mr;
    char    *me;
    char    *vi;
    char    *ve;
}	t_termcaps;

typedef struct s_select
{
	struct termios		orig_termios;
	struct winsize		win_size;
	struct s_string		buf;
	struct s_cursor		cursor;
	struct s_termcaps	termcaps;

	char			**av;
	int				ac;

	int				fd_tty;
	int				fd_logfile;

}	t_select;

/* ENUMERATIONS */

enum e_key
{
	KEY_UP = 1000,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SPACE,
	KEY_ENTER,
	KEY_ESC,
	KEY_BACKSPACE,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGE_UP,
	KEY_PAGE_DOWN,
	KEY_UNKNOWN
};

/* PROTOTYPES */

// signal.c
void	setup_signal_handlers(struct s_select *s);

// conf.c
void	enable_raw_mode(struct s_select *s);
void	disable_raw_mode(struct s_select *s);
int		get_window_size(struct s_select *s);

// keys.c
int		ctrl_key(const int k);
int		editor_read_key(struct s_select *s);

// moves.c
void	handle_up_key(struct s_select *s);
void	handle_down_key(struct s_select *s);
void    handle_right_key(struct s_select *s);
void    handle_left_key(struct s_select *s);

// render.c
void	render_terminal(struct s_select *s);
void	editor_process_keypress(struct s_select *s);
void	editor_refresh_screen(struct s_select *s);
void	editor_draw_arguments(struct s_select *s);

// buffer.c
void	append_buffer(struct s_select *s, const char *str, int len);
void	write_buffer(int fd, struct s_string buf);
void	clear_buffer(struct s_select *s);

// termcap.c
void	tc_move_cursor(struct s_select *s);
void	tc_clear_screen(void);

void	log_info(struct s_select *s, const char *str);
void	fatal_error(const char *msg, struct s_select *s);

#endif