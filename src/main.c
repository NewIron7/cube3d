/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:27:08 by hboissel          #+#    #+#             */
/*   Updated: 2023/06/27 11:12:44 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close(t_app *app)
{
	if (app)
	{
		if (app->mlx_ptr)
		{
			if (app->img.ptr)
				mlx_destroy_image(app->mlx_ptr, app->img.ptr);
			if (app->win_ptr)
				mlx_destroy_window(app->mlx_ptr, app->win_ptr);
			mlx_destroy_display(app->mlx_ptr);
			free(app->mlx_ptr);
		}
	}
	exit(EXIT_SUCCESS);
}

static int	render(void *app_render)
{
	t_app	*app;

	app = (t_app *)app_render;
	do_player_move(app);
	raycasting(app);
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, app->img.ptr, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_app	app;

	(void)argc;
	(void)argv;
	init_struct(&app);
	app.mlx_ptr = mlx_init();
	ft_error_mlx(&app);
	app.win_ptr = mlx_new_window(app.mlx_ptr, W_WIDTH, W_HEIGHT, W_NAME);
	ft_error_malloc(app.win_ptr, &app, "MLX ERROR: can't create a window");
	new_img(&app, app.mlx_ptr, W_WIDTH, W_HEIGHT);
	init_raycasting(&app);
	mlx_put_image_to_window(app.mlx_ptr, app.win_ptr, app.img.ptr, 0, 0);
	mlx_loop_hook(app.mlx_ptr, render, &app);
	mlx_hook(app.win_ptr, 17, 0, ft_close, &app);
	mlx_hook(app.win_ptr, 2, 1L << 0, handle_key_press, &app);
	mlx_hook(app.win_ptr, 3, 1L << 1, handle_key_release, &app);
	mlx_do_sync(app.mlx_ptr);
	mlx_loop(app.mlx_ptr);
	return (0);
}
