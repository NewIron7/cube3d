/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:54:52 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/22 09:44:56 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
/*
void	refresh_img(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->size.y)
	{
		i = 0;
		while (x < img->size.x)
		{
			put_pixel(img, x, y, 0x00000000);
			i++;
		}
		y++;
	}
}*/

void	player_move_straight(t_pvect *player, t_map *map)
{
	t_dpoint	dir_move;

	dir_move = mult_dpoint(player->dir, COEF_MOVE);
	dir_move = sum_dpoint(player->pos, dir_move);
	//check collision
	if (dir_move.x >= 0 && dir_move.x < map->size.x
		&& dir_move.y > 0 && dir_move.y < map->size.y)
		player->pos = dir_move;
}

int	handle_key_press(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
		ft_close(app);
	else if (keycode == 65361)
		app->player.dir = rotate_vect(&app->player.dir, -ROT_ANGLE);
	else if (keycode == 65363)
		app->player.dir = rotate_vect(&app->player.dir, ROT_ANGLE);
	else if (keycode == 'w')
		player_move_straight(&app->player, &app->map);
	raycasting(app->player, &app->map, &app->img);
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, app->img.ptr, 0, 0);
	return (0);
}
