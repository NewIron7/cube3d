/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_screen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 00:24:50 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/24 16:58:57 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_screen	get_screen_left(void)
{
	t_screen	screen;

	screen.panel = PANEL;
	screen.step = (PANEL * 2) / W_WIDTH;
	return (screen);
}

t_screen	get_screen_right(void)
{
	t_screen	screen;

	screen.step = (PANEL * 2) / W_WIDTH;
	screen.panel = (PANEL * 2) / W_WIDTH;
	return (screen);
}
