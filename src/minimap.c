/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:34:49 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/23 18:52:03 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_direction(t_point square, t_dpoint dir, t_img *img)
{
	t_point	end;
	t_point	multi;

	square.x += MM_ELEM / 2 + 1;
	square.y += MM_ELEM / 2 + 1;
	end.x = 100 * dir.x;
	end.y = 100 * dir.y;
	if (end.x < 0)
		multi.x = -1;
	else
		multi.x = 1;
	end.x = square.x + end.x * multi.x;
	if (end.y < 0)
		multi.y = -1;
	else
		multi.y = 1;
	end.y = square.y + end.y * multi.y;
	ft_plotLine(square, end, multi, img);
}

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

static void	draw_minimap(t_app *app, t_point start, t_point pos)
{
	int		i;
	int		j;
	t_point	square;
	
	i = 0;
	while (i < MM_HRANGE * 2 + 1 && i + start.x < app->map.size.x)
	{
		square.x = i * MM_ELEM + MM_OFFSET;
		j = 0;
		while (j < MM_VRANGE * 2 + 1 && j + start.y < app->map.size.y)
		{
			square.y = j * MM_ELEM + MM_OFFSET;
			if (start.x + i == pos.x && start.y + j == pos.y)
			{
				draw_square(square, C_MM_PLAYER, &app->img);
				draw_direction(square, app->player.dir, &app->img);
			}
			else if (app->map.map[start.y + j][start.x + i] == CHAR_WALL)
				draw_square(square, C_MM_WALL, &app->img);
			else
				draw_square(square, C_MM_FLOOR, &app->img);
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
	draw_minimap(app, start, pos);
}
