/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_mouse_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 09:03:31 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/21 09:22:26 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	do_mouse_move(t_app *app)
{
	int		x;
	int		y;
	double	rot;

	if (!mlx_mouse_get_pos(app->mlx_ptr, app->win_ptr, &x, &y))
		return ;
	mlx_mouse_move(app->mlx_ptr, app->win_ptr, W_WIDTH / 2, W_HEIGHT / 2);
	if (x == W_WIDTH / 2)
		return ;
	else if (x > W_WIDTH / 2)
		rot = ROT_ANGLE * (x - W_WIDTH / 2);
	else
		rot = -ROT_ANGLE * (W_WIDTH / 2 - x);
	app->player.dir = rotate_vect(&app->player.dir, rot);
}
