/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:48:22 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 15:48:27 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"
#include "../libft/libft.h"

void	control_key(struct s_select *s, int key)
{
	if (key == KEY_ESCAPE)
	{
		disable_raw_mode();
		log_info(s, "Exiting program");
		exit(EXIT_SUCCESS);
	}
	else if (key == KEY_SPACE)
		log_info(s, "Space key pressed");
	else if (key == KEY_ENTER)
		log_info(s, "Enter key pressed");
	else if (key == KEY_BACKSPACE || key == KEY_DELETE)
		log_info(s, "Delete key pressed");
}
