/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_step.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:45:24 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/31 15:15:23 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_first_step_x(t_pvect vect)
{
	double	step;

	if (vect.dir.x > 0)
		step = ceil(vect.pos.x) - vect.pos.x;
	else if (vect.dir.x < 0)
		step = trunc(vect.pos.x) - vect.pos.x;
	else
		step = 0;
	return (step);
}

double	get_first_step_y(t_pvect vect)
{
	double	step;

	if (vect.dir.y > 0)
		step = ceil(vect.pos.y) - vect.pos.y;
	else if (vect.dir.y < 0)
		step = trunc(vect.pos.y) - vect.pos.y;
	else
		step = 0;
	return (step);
}
