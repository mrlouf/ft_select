/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:15:42 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/28 12:34:05 by nicolas          ###   ########.fr       */
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

// Bonus
# include <sys/stat.h>

# include "../libft/inc/libft.h"

/* MACROS */

# define HEADER_INFO "ft_select - A terminal-based selection tool"
# define TILDE "~ "
# define TILDE_OFFSET 2

# define C_GREEN	"\033[32m"
# define C_BLUE		"\033[34m"
# define C_CYAN		"\033[36m"
# define C_MAGENTA	"\033[35m"
# define C_YELLOW	"\033[33m"
# define C_RESET	"\033[0m"

# define TC_UNDERLINE_START	"\033[4m"
# define TC_UNDERLINE_END	"\033[24m"

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
	u_int8_t			*selected;
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
void	tc_hide_cursor(struct s_select *s);
void	tc_show_cursor(struct s_select *s);
void	tc_invert_colours(struct s_select *s);
void	tc_reset_colours(struct s_select *s);
void	tc_start_underline(struct s_select *s);
void	tc_stop_underline(struct s_select *s);

#endif