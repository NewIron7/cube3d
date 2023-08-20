/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 14:01:02 by hboissel          #+#    #+#             */
/*   Updated: 2023/08/21 01:08:10 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	next_dir_screen_left(t_screen *screen, t_pvect *player)
{
	double	angle;

	angle = -PI_2 + atan(1 / screen->panel);
	screen->dir.x = player->dir.x * cos(angle) - player->dir.y * sin(angle);
	screen->dir.y = player->dir.x * sin(angle) + player->dir.y * cos(angle);
	screen->panel -= screen->step;
	return (angle);
}

double	next_dir_screen_right(t_screen *screen, t_pvect *player)
{
	double	angle;

	angle = PI_2 - atan(1 / screen->panel);
	screen->dir.x = player->dir.x * cos(angle) - player->dir.y * sin(angle);
	screen->dir.y = player->dir.x * sin(angle) + player->dir.y * cos(angle);
	screen->panel += screen->step;
	return (angle);
}

int	do_raycasting_left(t_pvect *player, t_screen *screen, t_app *app)
{
	int		i;
	t_wall	wall;
	double	angle;

	i = 0;
	while (screen->panel >= 0)
	{
		angle = next_dir_screen_left(screen, player);
		wall = get_coord_wall(screen->dir, player->pos, &app->map);
		wall.dist *= cos(angle);
		print_wall_textured(i, &wall, app);
		i++;
	}
	return (i);
}

void	do_raycasting_right(
			t_pvect *player,
			t_screen *screen,
			t_app *app,
			int i)
{
	t_wall	wall;
	double	angle;

	while (screen->panel <= PANEL && i < W_WIDTH)
	{
		angle = next_dir_screen_right(screen, player);
		wall = get_coord_wall(screen->dir, player->pos, &app->map);
		wall.dist *= cos(-angle);
		print_wall_textured(i, &wall, app);
		i++;
	}
}

void	raycasting(t_app *app)
{
	t_screen	screen;
	int			i;
	t_pvect		player;

	player = app->player;
	screen = get_screen_left();
	i = do_raycasting_left(&player, &screen, app);
	screen = get_screen_right();
	do_raycasting_right(&player, &screen, app, i);
}
