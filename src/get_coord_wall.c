/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:45:05 by hboissel          #+#    #+#             */
/*   Updated: 2023/08/31 15:16:07 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_coord_wall_x(t_pvect player, t_map *map, t_wall *wall)
{
	double	n;
	double	step;

	wall->dist = 0;
	n = player.dir.y / player.dir.x;
	step = get_first_step_x(player);
	wall->orient = EAST;
	if (step <= 0)
		wall->orient = WEST;
	wall->dir = next_wall_x(&player.pos, n, step);
	step = 1;
	if (wall->orient == WEST)
		step = -1;
	while (1)
	{
		if (is_wall_x(wall, map))
			break ;
		wall->dir = next_wall_x(&player.pos, n, step);
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
	if (step <= 0)
		wall->orient = NORTH;
	wall->dir = next_wall_y(&player.pos, n, step);
	step = 1;
	if (wall->orient == NORTH)
		step = -1;
	while (1)
	{
		if (is_wall_y(wall, map))
			break ;
		wall->dir = next_wall_y(&player.pos, n, step);
	}
}

static void	get_coord_wall_straight_y(t_pvect player, t_map *map, t_wall *wall)
{
	double	step;

	step = get_first_step_y(player);
	wall->orient = SOUTH;
	if (step <= 0)
		wall->orient = NORTH;
	wall->dist = fabs(step);
	wall->dir = next_wall_y(&player.pos, 0, step);
	step = 1;
	if (wall->orient == NORTH)
		step = -1;
	while (1)
	{
		if (is_wall_y(wall, map))
			break ;
		wall->dist++;
		wall->dir = next_wall_x(&player.pos, 0, step);
	}
}

static void	get_coord_wall_straight_x(t_pvect player, t_map *map, t_wall *wall)
{
	double	step;

	step = get_first_step_x(player);
	wall->orient = EAST;
	if (step <= 0)
		wall->orient = WEST;
	wall->dist = fabs(step);
	wall->dir = next_wall_x(&player.pos, 0, step);
	step = 1;
	if (wall->orient == WEST)
		step = -1;
	while (1)
	{
		if (is_wall_x(wall, map))
			break ;
		wall->dist++;
		wall->dir = next_wall_x(&player.pos, 0, step);
	}
}

t_wall	get_coord_wall(t_dpoint dir, t_dpoint pos, t_map *map)
{
	t_pvect	player;
	t_wall	tmp;
	t_wall	wall;

	cpy_dpoint(&pos, &player.pos);
	cpy_dpoint(&dir, &player.dir);
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
