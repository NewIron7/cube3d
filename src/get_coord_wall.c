/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coord_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 21:45:05 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/20 23:28:32 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	cpy_dpoint(t_dpoint *src, t_dpoint *dest)
{
	dest->x = src->x;
	dest->y = src->y;
}

void	calculate_move_coef(double x, double y, double *move)
{
	double tmp;

	if (x == 0)
		*move = 0;
	else
	{
		tmp = (y * y) / (x * x) + 1;
		*move = sqrt(tmp);
	}
}

double	get_first_step_x(t_pvect vect)
{
	double	step;

	if (vect.dir.x > vect.pos.x)
		step = 1 - vect.pos.x;
	else if (vect.dir.x < vect.pos.x)
		step = vect.pos.x;
	else
		step = 0;
	return (step);
}

double	get_first_step_y(t_pvect vect)
{
	double	step;

	if (vect.dir.y > vect.pos.y)
		step = 1 - vect.pos.y;
	else if (vect.dir.y < vect.pos.y)
		step = vect.pos.y;
	else
		step = 0;
	return (step);
}

t_dpoint	sum_pos_dir_coef(t_pvect vect, double coef)
{
	vect.dir.x *= coef;
	vect.dir.y *= coef;
	vect.pos.x += tmp_dir.x;
	vect.pos.y += tmp_dir.y;
	return (vect.pos);
}

char	check_wall(t_pvect *wall, t_dpoint pos, t_map map)
{
	int	x;
	int	y;

	x = (int)wall->dir.x;
	y = (int)wall->dir.y;
	if (
}

double	get_coord_x_wall(double mx, t_pvect vect, t_map map, t_pvect *wall)
{
	double	step;
	double	dist;

	dist = 0;
	step = get_first_step_x(vect);
	while (step)
	{
		dist = step * mx;
		wall->dir = sum_pos_dir_coef(&vect, step * mx);
		if (check_wall(wall, vect.pos, map))
			return (dist);
		step = 1;
	}
}

double	get_coord_wall(t_dpoint dir, t_dpoint pos, t_map map, t_pvect *wall)
{
	double	mx;
	double	my;
	double	dist;
	t_pvect	vect;

	calculate_move_coef(dir.x, dir.y, &mx);
	calculate_move_coef(dir.y, dir.x, &my);
	cpy_dpoint(&dir, &vect.dir);
	cpy_dpoint(&pos, &vect.pos);
	dist = get_coord_x_wall(mx, vect, map, wall);

}

void	test_get_coord_wall(void)
{
	char	tmp[10][24] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	t_map	map;
	t_dpoint	dir;
	t_dpoint	pos;
	t_pvect		result;
	double		dist;

	map.map = tmp;
	map.size.x = 24;
	map.size.y = 10;
	dir.x = 0;
	dir.y = 1;
	pos.x = 1;
	pos.y = 9;
	dist = get_coord_wall(dir, pos, map, &result);
	printf("RESULT: (x) %f, (y) %f, dist = %f\n", result.pos.x, result.pos.y, dist);
}
