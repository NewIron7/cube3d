/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:49:32 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/20 16:49:42 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dpoint	next_wall_x(t_dpoint *pos, double n, double step)
{
	t_dpoint	wall;

	wall.x = step + pos->x;
	wall.y = (n * step) + pos->y;
	pos->x = wall.x;
	pos->y = wall.y;
	return (wall);
}

t_dpoint	next_wall_y(t_dpoint *pos, double n, double step)
{
	t_dpoint	wall;

	wall.y = step + pos->y;
	wall.x = (n * step) + pos->x;
	pos->x = wall.x;
	pos->y = wall.y;
	return (wall);
}
