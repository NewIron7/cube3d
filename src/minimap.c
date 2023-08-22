/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:34:49 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/22 18:03:36 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_point square, unsigned int color, t_img *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < MM_ELEM)
	{
		j = 0;
		while (j < MM_ELEM)
		{
			put_pixel(img, i + square.x, j + square.y, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap(t_map *map, t_point start, t_point pos, t_img *img)
{
	int		i;
	int		j;
	t_point	square;
	
	i = 0;
	while (i < MM_HRANGE * 2 + 1 && i + start.x < map->size.x)
	{
		square.x = i * MM_ELEM + MM_OFFSET;
		j = 0;
		while (j < MM_VRANGE * 2 + 1 && j + start.y < map->size.y)
		{
			square.y = j * MM_ELEM + MM_OFFSET;
			if (start.x + i == pos.x && start.y + j == pos.y)
				draw_square(square, C_MM_PLAYER, img);
			else if (map->map[start.y + j][start.x + i] == CHAR_WALL)
				draw_square(square, C_MM_WALL, img);
			else
				draw_square(square, C_MM_FLOOR, img);
			j++;
		}
		i++;
	}
}

static int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

void	minimap(t_app *app)
{
	t_point	pos;
	t_point	start;

	pos.x = app->player.pos.x;
	pos.y = app->player.pos.y;
	start.x = ft_max(pos.x - MM_HRANGE, 0);
	start.y = ft_max(pos.y - MM_VRANGE, 0);
	draw_minimap(&app->map, start, pos, &app->img);
}
