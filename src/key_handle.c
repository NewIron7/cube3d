/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:54:52 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/26 15:41:29 by hboissel         ###   ########.fr       */
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

static char	check_exit_map(t_dpoint move, t_map *map)
{
	if (move.x >= 0 && move.x < map->size.x
		&& move.y > 0 && move.y < map->size.y)
		return (0);
	return (1);
}

static char	check_collisions(t_pvect *player, t_dpoint *move, t_map *map)
{
	t_point pmove;

	(void)player;
	pmove.x = move->x;
	pmove.y = move->y;
	if (map->map[pmove.y][pmove.x])
	{/*//Systeme de collisons ou l'on glisse contre le mur
		if (map->map[pmove.y][(int)player->pos.x] == 0)
			move->x = (int)player->pos.x;
		else if (map->map[(int)player->pos.y][pmove.x] == 0)
			move->y = (int)player->pos.y;
		else*/
			return (1);
	}
	return (0);
}

void	player_move(t_pvect *player, t_map *map, char move, int speed)
{
	t_dpoint	dir_move;

	if (move == E_W_KEY)
		dir_move = mult_dpoint(player->dir, COEF_MOVE * speed);
	else if (move == E_S_KEY)
		dir_move = mult_dpoint(player->dir, -COEF_MOVE * speed);
	else
	{
		dir_move = get_vect_orth(player->dir);
		if (move == E_A_KEY)
			dir_move = mult_dpoint(dir_move, -COEF_MOVE_SIDE * speed);
		if (move == E_D_KEY)
			dir_move = mult_dpoint(dir_move, COEF_MOVE_SIDE * speed);
	}
	dir_move = sum_dpoint(player->pos, dir_move);
	//check collision
	if (!check_exit_map(dir_move, map) && !check_collisions(player, &dir_move, map))
		player->pos = dir_move;
	//printf("%f, %f\n", player->pos.x, player->pos.y);
}
/*
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
}*/

void	do_player_move(t_app *app)
{
	int	speed;

	speed = 1;
	if (app->keys[E_SHIFT_KEY])
		speed = 2;
	if (app->keys[E_W_KEY])
		player_move(&app->player, &app->map, E_W_KEY, speed);
	if (app->keys[E_S_KEY])
		player_move(&app->player, &app->map, E_S_KEY, speed);
	if (app->keys[E_A_KEY])
		player_move(&app->player, &app->map, E_A_KEY, speed);
	if (app->keys[E_D_KEY])
		player_move(&app->player, &app->map, E_D_KEY, speed);
	if (app->keys[E_LEFT_KEY])
		app->player.dir = rotate_vect(&app->player.dir, -ROT_ANGLE * speed);
	if (app->keys[E_RIGHT_KEY])
		app->player.dir = rotate_vect(&app->player.dir, ROT_ANGLE * speed);
}

int	handle_key_press(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
		ft_close(app);
	else if (keycode == KEY_LEFT)
		app->keys[E_LEFT_KEY] = 1;
	else if (keycode == KEY_RIGHT)
		app->keys[E_RIGHT_KEY] = 1;
	else if (keycode == 'w')
		app->keys[E_W_KEY] = 1;
	else if (keycode == 's')
		app->keys[E_S_KEY] = 1;
	else if (keycode == 'a')
		app->keys[E_A_KEY] = 1;
	else if (keycode == 'd')
		app->keys[E_D_KEY] = 1;
	else if (keycode == KEY_SHIFT)
		app->keys[E_SHIFT_KEY] = 1;
	//printf("%d\n", keycode);
	return (0);
}

int	handle_key_release(int keycode, t_app *app)
{
	if (keycode == KEY_LEFT)
		app->keys[E_LEFT_KEY] = 0;
	else if (keycode == KEY_RIGHT)
		app->keys[E_RIGHT_KEY] = 0;
	else if (keycode == 'w')
		app->keys[E_W_KEY] = 0;
	else if (keycode == 's')
		app->keys[E_S_KEY] = 0;
	else if (keycode == 'a')
		app->keys[E_A_KEY] = 0;
	else if (keycode == 'd')
		app->keys[E_D_KEY] = 0;
	else if (keycode == KEY_SHIFT)
		app->keys[E_SHIFT_KEY] = 0;
	return (0);
}
