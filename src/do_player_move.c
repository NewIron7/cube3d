/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_player_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 22:12:34 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/20 22:13:02 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	update_pos_x(
					double pos_x,
					double move_x,
					double pos_y,
					char **map)
{
	int		y_out;
	int		y_in;
	int		future_x;

	y_in = (int)(pos_y + BODY_SIZE);
	y_out = (int)(pos_y - BODY_SIZE);
	if (move_x < 0)
		future_x = (int)(pos_x + move_x - BODY_SIZE);
	else
		future_x = (int)(pos_x + move_x + BODY_SIZE);
	if (map[y_in][future_x] != CHAR_WALL
		&& map[y_out][future_x] != CHAR_WALL)
		pos_x += move_x;
	return (pos_x);
}

static double	update_pos_y(
					double pos_y,
					double move_y,
					double pos_x,
					char **map)
{
	int		x_out;
	int		x_in;
	int		future_y;

	x_in = (int)(pos_x + BODY_SIZE);
	x_out = (int)(pos_x - BODY_SIZE);
	if (move_y < 0)
		future_y = (int)(pos_y + move_y - BODY_SIZE);
	else
		future_y = (int)(pos_y + move_y + BODY_SIZE);
	if (map[future_y][x_in] != CHAR_WALL
		&& map[future_y][x_out] != CHAR_WALL)
		pos_y += move_y;
	return (pos_y);
}

static void	player_move(
				t_pvect *player,
				t_map *map,
				char move,
				int speed)
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
	player->pos.x = update_pos_x(
			player->pos.x, dir_move.x, player->pos.y, map->map);
	player->pos.y = update_pos_y(
			player->pos.y, dir_move.y, player->pos.x, map->map);
}

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
