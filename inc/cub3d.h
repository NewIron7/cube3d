/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboissel <hboissel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 18:20:59 by hboissel          #+#    #+#             */
/*   Updated: 2023/08/31 16:36:45 by ddelhalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"
# include "mlx.h"

# define W_WIDTH 1280
# define W_HEIGHT 720
# define W_NAME "cub3d"

# define MM_HRANGE 15
# define MM_VRANGE 10
# define MM_ELEM 5
# define MM_OFFSET 20
# define C_MM_WALL 0x00303030
# define C_MM_FLOOR 0x00A08020
# define C_MM_PLAYER 0x00202080
# define C_MM_DIRECTION 0x00FF0000

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SHIFT 65505
# define KEY_CTRL 65507

# define C_RED 0x00FF0000
# define C_GREEN 0x0000FF00

# define C_NORTH 0x00c27ba0 //pink
# define C_SOUTH 0x00783f04//dark brow
# define C_EAST 0x00f1c232 //yellow
# define C_WEST	0x007f6000 //brown
# define C_GROUND 0x009b7653 //dirt
# define C_CEILING 0x00282130 //black

# define DFL_TXTR_NO "textures/brick.xpm"
# define DFL_TXTR_SO "textures/metal.xpm"
# define DFL_TXTR_WE "textures/wood.xpm"
# define DFL_TXTR_EA "textures/stone.xpm"

# define FILE_EXT ".cub"

# define REALLOC_BUFF_SIZE 10

# define PANEL 0.5773502692

# define WALL_SIZE 1.5
# define DIST_COL 0.49
# define ROT_ANGLE 0.02
# define MOUSE_ANGLE 0.002
# define COEF_MOVE 0.05
# define COEF_MOVE_SIDE 0.04
# define PLAYER_HEIGHT 0.5
# define BODY_SIZE 0.1

# define PI_6 0.5235987756
# define PI_4 0.7853981634
# define PI_3 1.047197551
# define PI_2 1.570796327
# define TAN_60 1.732050808
# define COS_60 0.5
# define SIN_60 0.8660254038
# define SIN_30 0.5
# define COS_30 0.8660254038
# define A_DIST -0.02564102564
# define B_DIST 1.012820513
# define ANGLE PI_3

# define CHAR_WALL 49
# define CHAR_BLANK 48

enum e_keys
{
	E_W_KEY,
	E_A_KEY,
	E_S_KEY,
	E_D_KEY,
	E_LEFT_KEY,
	E_RIGHT_KEY,
	E_SHIFT_KEY,
	E_CTRL_KEY
};

enum e_orient
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

enum e_types
{
	FLOOR,
	CEILING,
	LINE_NORTH,
	LINE_SOUTH,
	LINE_WEST,
	LINE_EAST,
	MAP,
	EMPTY
};

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef struct s_screen
{
	double		panel;
	double		step;
	t_dpoint	dir;
}	t_screen;

typedef struct s_pvect
{
	t_dpoint	pos;
	t_dpoint	dir;
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
	char	**map;
	t_point	size;
}	t_map;

typedef struct s_app
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_map			map;
	t_img			img;
	t_pvect			player;
	char			keys[8];
	t_img			textures[4];
	unsigned int	colors[2];
}	t_app;

int				init_raycasting(t_app *app);

void			new_img(t_app *app, void *mlx, int width, int height);
void			put_pixel(t_img *img, int x, int y, unsigned int color);
unsigned int	get_color_pixel(t_img *img, int x, int y);
int				load_textures(t_app *app, char *filenames[]);

t_wall			get_coord_wall(t_dpoint dir, t_dpoint pos, t_map *map);
void			raycasting(t_app *app);
void			print_wall_textured(int x, t_wall *wall, t_app *app);

t_dpoint		mult_dpoint(t_dpoint a, double coef);
t_dpoint		sum_dpoint(t_dpoint a, t_dpoint b);
void			cpy_dpoint(t_dpoint *src, t_dpoint *dest);
t_dpoint		rotate_vect(t_dpoint *vect, double angle);
t_dpoint		get_vect_orth(t_dpoint a);

void			ft_error_mlx(t_app *app);
void			ft_error_malloc(const void *ptr, t_app *app, char *str);

int				handle_key_press(int keycode, t_app *app);
int				handle_key_release(int keycode, t_app *app);
void			do_player_move(t_app *app);

int				ft_close(t_app *app);

void			test_get_coord_wall(t_img *img);

int				read_file(char *filename, t_app *app);
int				load_file(t_app *app, int fd, char *textures[]);
int				check_line(char *line, char *prev, t_app *app);
int				load_map(char *line, int fd, t_app *app);
int				process_setting(char *line, int type,
					t_app *app, char *textures[]);
int				write_error(char *err);
void			free_map(char **map);

t_screen		get_screen_left(void);
t_screen		get_screen_right(void);

double			get_first_step_x(t_pvect vect);
double			get_first_step_y(t_pvect vect);
t_dpoint		next_wall_x(t_dpoint *pos, double n, double step);
t_dpoint		next_wall_y(t_dpoint *pos, double n, double step);
char			is_wall_x(t_wall *wall, t_map *map);
char			is_wall_y(t_wall *wall, t_map *map);
double			get_dist_wall(t_pvect *player, t_wall *wall);
void			minimap(t_app *app);

void			do_mouse_move(t_app *app);
void			ft_plotline(t_point p1, t_point p2, t_point multi, t_img *img);

#endif
