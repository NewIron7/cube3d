/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_first_step.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:45:24 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/20 16:46:54 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_first_step_x(t_pvect vect)
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

double	get_first_step_y(t_pvect vect)
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
