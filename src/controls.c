/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 13:48:22 by nicolas           #+#    #+#             */
/*   Updated: 2026/05/25 14:00:08 by nicolas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/ft_select.h"
# include "../libft/libft.h"

void	editor_control_key(struct s_select *s, int key)
{
    (void)s;

    if (key == KEY_ESCAPE)
    {
        disable_raw_mode();
        exit(EXIT_SUCCESS);
    }

}