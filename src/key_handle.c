/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:54:52 by hboissel          #+#    #+#             */
/*   Updated: 2023/08/20 20:00:37 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	check_exit_map(t_dpoint move, t_map *map)
{
	if (move.x >= 0 && move.x < map->size.x
		&& move.y > 0 && move.y < map->size.y)
		return (0);
	return (1);
}

static t_dpoint	update_pos(t_dpoint pos, t_dpoint move, char **map)
{
	t_dpoint	new_pos;
	double		body_size;

	body_size = BODY_SIZE;
	if (move.x < 0)
		body_size = -body_size;
	new_pos.x = pos.x;
	if (map[(int) (pos.y + BODY_SIZE)][(int) (pos.x + move.x + body_size)] != CHAR_WALL
		&& map[(int) (pos.y - BODY_SIZE)][(int) (pos.x + move.x + body_size)] != CHAR_WALL)
		new_pos.x += move.x;
	body_size = BODY_SIZE;
	if (move.y < 0)
		body_size = -body_size;
	new_pos.y = pos.y;
	if (map[(int) (pos.y + move.y + body_size)][(int) (pos.x + BODY_SIZE)] != CHAR_WALL
		&& map[(int) (pos.y + move.y + body_size)][(int) (pos.x - BODY_SIZE)] != CHAR_WALL)
		new_pos.y += move.y;
	return (new_pos);
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
	player->pos = update_pos(player->pos, dir_move, map->map);
	//check collision
	if (!check_exit_map(dir_move, map)
		&& map->map[(int) dir_move.y][(int) dir_move.x] != CHAR_WALL)
		;
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
