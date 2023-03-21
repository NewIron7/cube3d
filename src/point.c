/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:23:09 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/21 11:23:11 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	cpy_dpoint(t_dpoint *src, t_dpoint *dest)
{
	dest->x = src->x;
	dest->y = src->y;
}

t_dpoint	sum_dpoint(t_dpoint a, t_dpoint b)
{
	t_dpoint	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return (result);
}

t_dpoint	mult_dpoint(t_dpoint a, double coef)
{
	t_dpoint	result;

	result.x = a.x * coef;
	result.y = a.y * coef;
	return (result);
}
