/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:50:28 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/20 16:53:56 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	is_wall_x(t_wall *wall, t_map *map)
{
	wall->pos.x = (int)wall->dir.x;
	if (wall->orient == WEST)
		wall->pos.x -= 1;
	wall->pos.y = (int)wall->dir.y;
	if (wall->pos.y < 0 || wall->pos.y >= map->size.y
		|| wall->pos.x < 0 || wall->pos.x >= map->size.x)
		return (1);
	if (map->map[wall->pos.y][wall->pos.x] == CHAR_WALL)
		return (1);
	else
		return (0);
}

char	is_wall_y(t_wall *wall, t_map *map)
{
	wall->pos.y = (int)wall->dir.y;
	if (wall->orient == NORTH)
		wall->pos.y -= 1;
	wall->pos.x = (int)wall->dir.x;
	if (wall->pos.y < 0 || wall->pos.y >= map->size.y
		|| wall->pos.x < 0 || wall->pos.x >= map->size.x)
		return (1);
	if (map->map[wall->pos.y][wall->pos.x] == CHAR_WALL)
		return (1);
	else
		return (0);
}
