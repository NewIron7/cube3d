/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 08:54:52 by hboissel          #+#    #+#             */
/*   Updated: 2023/08/31 16:37:27 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key_press(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
		ft_close(app);
	else if (keycode == KEY_LEFT)
		app->keys[E_LEFT_KEY] = 1;
	else if (keycode == KEY_RIGHT)
		app->keys[E_RIGHT_KEY] = 1;
	else if (keycode == 'w')
		app->keys[E_W_KEY] = 1;
	else if (keycode == 's')
		app->keys[E_S_KEY] = 1;
	else if (keycode == 'a')
		app->keys[E_A_KEY] = 1;
	else if (keycode == 'd')
		app->keys[E_D_KEY] = 1;
	else if (keycode == KEY_SHIFT)
		app->keys[E_SHIFT_KEY] = 1;
	else if (keycode == KEY_CTRL)
		app->keys[E_CTRL_KEY] = 1;
	return (0);
}

int	handle_key_release(int keycode, t_app *app)
{
	if (keycode == KEY_LEFT)
		app->keys[E_LEFT_KEY] = 0;
	else if (keycode == KEY_RIGHT)
		app->keys[E_RIGHT_KEY] = 0;
	else if (keycode == 'w')
		app->keys[E_W_KEY] = 0;
	else if (keycode == 's')
		app->keys[E_S_KEY] = 0;
	else if (keycode == 'a')
		app->keys[E_A_KEY] = 0;
	else if (keycode == 'd')
		app->keys[E_D_KEY] = 0;
	else if (keycode == KEY_SHIFT)
		app->keys[E_SHIFT_KEY] = 0;
	else if (keycode == KEY_CTRL)
		app->keys[E_CTRL_KEY] = 0;
	return (0);
}
