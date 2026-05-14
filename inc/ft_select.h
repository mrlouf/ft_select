/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:15:42 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/14 20:10:20 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

/* INCLUDES */

# include <stdlib.h>
# include <unistd.h>
# include <termios.h>
# include <errno.h>

/* STRUCTURES */

typedef struct s_select
{
	struct termios	orig_termios;

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

void	disable_raw_mode(struct termios *orig_termios);
int		ctrl_key(const int k);
char	editor_read_key(void);
void	fatal_error(const char *msg);
void	editor_process_keypress(struct s_select *s);
void	editor_refresh_screen(void);

#endif