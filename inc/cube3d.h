/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:20:59 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/20 22:37:51 by hboissel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"
# include "mlx.h"

# define W_WIDTH 720
# define W_HEIGHT 480
# define W_NAME "cube3d"

typedef struct s_dpoint
{
	double x;
	double y;
}	t_dpoint;

typedef struct s_pvect
{
	t_dpoint pos;
	t_dpoint dir;
}	t_pvect;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_img
{
	void	*ptr;
	t_point	size;
	char	*pxls;
	int		bpp;
	int		line_s;
	int		endian;
}	t_img;

typedef struct s_map
{
	char **map;
	t_point size;
}	t_map;

typedef struct s_app
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_map			map;
	t_img			img;
}	t_app;

void	init_struct(t_app *app);
void    new_img(t_app *app, void *mlx, int width, int height);
void	put_pixel(t_img *img, int x, int y, int color);

void    ft_error_mlx(t_app *app);
void    ft_error_malloc(const void *ptr, t_app *app, char *str);

int		ft_close(t_app *app);

void	test_get_coord_wall(void);
#endif
