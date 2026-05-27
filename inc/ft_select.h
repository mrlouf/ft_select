/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:15:42 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/26 18:57:13 by nicolas          ###   ########.fr       */
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

# include "../libft/inc/libft.h"

/* MACROS */

# define HEADER_INFO "ft_select - A terminal-based selection tool"
# define TILDE "~ "
# define TILDE_OFFSET 2

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
	char	*cm;
	char	*cl;
	char	*mr;
	char	*me;
	char	*vi;
	char	*ve;
	char	*smul;
	char	*rmul;
}	t_termcaps;

typedef struct s_select
{
	struct s_string		buf;
	struct s_termcaps	termcaps;
	struct s_cursor		cursor;
	struct winsize		win_size;

	char				**av;
	unsigned char		selected;
	int					ac;

	int					fd_tty;
	int					fd_logfile;

}	t_select;

/* GLOBAL VARIABLES */

extern struct termios	g_orig_termios;
extern int				g_fd_tty;

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
	KEY_ESCAPE,
	KEY_UNKNOWN
};

/* PROTOTYPES */

// signal.c
void	setup_signal_handlers(void);

// conf.c
void	enable_raw_mode(void);
void	disable_raw_mode(void);
int		get_window_size(struct s_select *s);
void	log_info(struct s_select *s, const char *str);
void	fatal_error(const char *msg);

// keys.c
void	process_keypress(struct s_select *s);

// moves.c
void	move_cursor(struct s_select *s, int key);

// controls.c
void	control_key(struct s_select *s, int key);

// render.c
void	render_terminal(struct s_select *s);

// buffer.c
void	append_buffer(struct s_select *s, const char *str, int len);
void	write_buffer(int fd, struct s_string buf);
void	clear_buffer(struct s_select *s);

// termcap.c
int		tc_callback(int c);
void	tc_move_cursor(struct s_select *s);
void	tc_clear_screen(struct s_select *s);
void	tc_putchar(struct s_select *s, char c);
void	tc_putstr(struct s_select *s, const char *str);
void	tc_putendl(struct s_select *s);
void	tc_set_cursor_visibility(struct s_select *s, int visible);
void	tc_invert_colours(struct s_select *s);
void	tc_reset_colours(struct s_select *s);
void	tc_start_underline(struct s_select *s);
void	tc_stop_underline(struct s_select *s);

#endif