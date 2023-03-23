/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:45:05 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/23 21:55:54 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static double	get_first_step_x(t_pvect vect)
{
	double	step;

	if (vect.dir.x > 0)
		step = ((int)vect.pos.x + 1) - vect.pos.x;
	else if (vect.dir.x < 0)
	{
		step = ((int)vect.pos.x) - vect.pos.x;
		if (step == 0)
			step = -1;
	}
	else
		step = 0;
	return (step);
}

static double	get_first_step_y(t_pvect vect)
{
	double	step;

	if (vect.dir.y > 0)
		step = ((int)vect.pos.y + 1) - vect.pos.y;
	else if (vect.dir.y < 0)
	{
		step = ((int)vect.pos.y) - vect.pos.y;
		if (step == 0)
			step = -1;
	}
	else
		step = 0;
	return (step);
}

static void	init_player(t_pvect *player, t_dpoint dir, t_dpoint pos)
{
	cpy_dpoint(&pos, &player->pos);
	cpy_dpoint(&dir, &player->dir);
}

static t_dpoint	next_wall_x(t_dpoint *pos, double n, double step)
{
	t_dpoint	wall;

	wall.x = step + pos->x;
	wall.y = (n * step) + pos->y;
	pos->x = wall.x;
	pos->y = wall.y;
	return (wall);
}

static t_dpoint	next_wall_y(t_dpoint *pos, double n, double step)
{
	t_dpoint	wall;

	wall.y = step + pos->y;
	wall.x = (n * step) + pos->x;
	pos->x = wall.x;
	pos->y = wall.y;
	return (wall);
}

static char	is_wall_x(t_wall *wall, t_map *map)
{
	wall->pos.x = (int)wall->dir.x;
	if (wall->orient == WEST)
		wall->pos.x -= 1;
	wall->pos.y = (int)wall->dir.y;
	if (wall->pos.y < 0 || wall->pos.y >= map->size.y
		|| wall->pos.x < 0 || wall->pos.x >= map->size.x)
		return (1);
	if (map->map[wall->pos.y][wall->pos.x])
		return (1);
	else
		return (0);
}

static char	is_wall_y(t_wall *wall, t_map *map)
{
	wall->pos.y = (int)wall->dir.y;
	if (wall->orient == NORTH)
		wall->pos.y -= 1;
	wall->pos.x = (int)wall->dir.x;
	if (wall->pos.y < 0 || wall->pos.y >= map->size.y
		|| wall->pos.x < 0 || wall->pos.x >= map->size.x)
		return (1);
	if (map->map[wall->pos.y][wall->pos.x])
		return (1);
	else
		return (0);
}

static void	get_coord_wall_x(t_pvect player, t_map *map, t_wall *wall)
{
	double	n;
	double	step;

	wall->dist = 0;
	n = player.dir.y / player.dir.x;
	step = get_first_step_x(player);
	wall->orient = EAST;
	if (step < 0)
		wall->orient = WEST;
	while (step)
	{
		wall->dir = next_wall_x(&player.pos, n, step);
		if (is_wall_x(wall, map))
			break ;
		step = 1;
		if (wall->orient == WEST)
			step = -1;
	}
}

static void	get_coord_wall_y(t_pvect player, t_map *map, t_wall *wall)
{
	double	n;
	double	step;

	wall->dist = 0;
	n = player.dir.x / player.dir.y;
	step = get_first_step_y(player);
	wall->orient = SOUTH;
	if (step < 0)
		wall->orient = NORTH;
	while (step)
	{
		wall->dir = next_wall_y(&player.pos, n, step);
		if (is_wall_y(wall, map))
			break ;
		step = 1;
		if (wall->orient == NORTH)
			step = -1;
	}
}

void	get_coord_wall_straight_y(t_pvect player, t_map *map, t_wall *wall)
{
	double	step;

	step = get_first_step_y(player);
	wall->orient = SOUTH;
	if (step < 0)
		wall->orient = NORTH;
	wall->dist = (step < 0) * (step * -1) + (step > 0) * step;
	while (step)
	{
		wall->dir = next_wall_y(&player.pos, 0, step);
		if (is_wall_y(wall, map))
			break ;
		wall->dist++;
		step = 1;
		if (wall->orient == NORTH)
			step = -1;
	}
}

void	get_coord_wall_straight_x(t_pvect player, t_map *map, t_wall *wall)
{
	double	step;

	step = get_first_step_x(player);
	wall->orient = EAST;
	if (step < 0)
		wall->orient = WEST;
	wall->dist = (step < 0) * (step * -1) + (step > 0) * step;
	while (step)
	{
		wall->dir = next_wall_x(&player.pos, 0, step);
		if (is_wall_x(wall, map))
			break ;
		wall->dist++;
		step = 1;
		if (wall->orient == WEST)
			step = -1;
	}
}

double	get_dist_wall(t_pvect *player, t_wall *wall)
{
	double	dist;

	dist = (wall->dir.x - player->pos.x) * (wall->dir.x - player->pos.x);
	dist += (wall->dir.y - player->pos.y) * (wall->dir.y - player->pos.y);
	dist = sqrt(dist);
	return (dist);
}

t_wall	get_coord_wall(t_dpoint dir, t_dpoint pos, t_map *map)
{
	t_pvect	player;
	t_wall	tmp;
	t_wall	wall;

	init_player(&player, dir, pos);
	if (player.dir.x == 0)
		get_coord_wall_straight_y(player, map, &wall);
	else if (player.dir.y == 0)
		get_coord_wall_straight_x(player, map, &wall);
	else
	{
		get_coord_wall_x(player, map, &wall);
		wall.dist = get_dist_wall(&player, &wall);
		get_coord_wall_y(player, map, &tmp);
		tmp.dist = get_dist_wall(&player, &tmp);
		if (tmp.dist < wall.dist)
			return (tmp);
		return (wall);
	}
	return (wall);
}
