/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_mouse_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 09:03:31 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/31 16:36:10 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	do_mouse_move(t_app *app)
{
	int		x;
	int		y;
	double	rot;

	if (app->keys[E_CTRL_KEY])
		return ;
	if (!mlx_mouse_get_pos(app->mlx_ptr, app->win_ptr, &x, &y))
		return ;
	if (x == W_WIDTH / 2)
		return ;
	else if (x > W_WIDTH / 2)
		rot = MOUSE_ANGLE * (double)(x - W_WIDTH / 2);
	else
		rot = -MOUSE_ANGLE * (double)(W_WIDTH / 2 - x);
	app->player.dir = rotate_vect(&app->player.dir, rot);
	mlx_mouse_move(app->mlx_ptr, app->win_ptr, W_WIDTH / 2, 0);
}
