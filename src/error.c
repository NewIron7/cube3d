/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:04:39 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/20 19:26:33 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_error_mlx(t_app *app)
{
	if (!app->mlx_ptr)
	{
		ft_putendl_fd("MLX ERROR", 2);
		exit(EXIT_FAILURE);
	}
}

void	ft_error_malloc(const void *ptr, t_app *app, char *str)
{
	if (!ptr)
	{
		if (str)
			ft_putendl_fd(str, 1);
		else
			ft_putendl_fd("MALLOC ERROR", 1);
		ft_close(app);
	}
}
