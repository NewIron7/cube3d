/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddelhalt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:30:34 by ddelhalt          #+#    #+#             */
/*   Updated: 2023/08/20 16:33:36 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_dist_wall(t_pvect *player, t_wall *wall)
{
	double	dist;

	dist = (wall->dir.x - player->pos.x) * (wall->dir.x - player->pos.x);
	dist += (wall->dir.y - player->pos.y) * (wall->dir.y - player->pos.y);
	dist = sqrt(dist);
	return (dist);
}
