/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:20:59 by hboissel          #+#    #+#             */
/*   Updated: 2023/03/21 10:58:20 by hboissel         ###   ########.fr       */
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

# define ANGLE -(M_PI * 2)/3

enum e_orient
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

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

typedef struct s_wall
{
	t_dpoint	dir;
	t_point		pos;
	char		orient;
	double		dist;
}	t_wall;

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

void	get_coord_wall(t_dpoint dir, t_dpoint pos, t_map *map, t_wall *wall);

t_dpoint	mult_dpoint(t_dpoint a, double coef);
t_dpoint	sum_dpoint(t_dpoint a, t_dpoint b);
void	cpy_dpoint(t_dpoint *src, t_dpoint *dest);

void    ft_error_mlx(t_app *app);
void    ft_error_malloc(const void *ptr, t_app *app, char *str);

int		ft_close(t_app *app);

void	test_get_coord_wall(void);
#endif
