/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:46:53 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/22 21:34:52 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "mlx.h"
# include "keycode.h"
# include <math.h>
# include <pthread.h>

# define WIN_WIDTH 1600
# define WIN_HEIGHT 900
# define MENU_WIDTH 400
# define MENU_COLOR 0x25292E
# define TEXT_COLOR 0x52B7BA
# define BORDER_COLOR 0xC8C9CB
# define TRANSPARENT -16777216
# define COLOR_RED 0xFF0000
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define NB_THREAD 4

typedef unsigned char	t_u8;

typedef struct s_pix	t_pix;
struct		s_pix
{
	int		iterations;
	double	c;
};

typedef struct s_rgb	t_rgb;
struct		s_rgb
{
	t_u8	b;
	t_u8	g;
	t_u8	r;
	t_u8	a;
};

typedef union s_color	t_color;
union		s_color
{
	t_rgb	rgb;
	int		color;
};

typedef struct s_vec2d	t_vec2d;
struct		s_vec2d
{
	int		x;
	int		y;
};

typedef struct s_image	t_image;
struct		s_image
{
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
};

typedef struct s_map	t_map;
struct		s_map
{
	t_image	*image;
	t_pix	(*processor)(double, double, t_map *);
	double	zoom;
	int		smooth;
	int		max_iter;
	double	x_offset;
	double	y_offset;
	double	real;
	double	imaginary;
};

typedef struct s_menu	t_menu;
struct		s_menu
{
	int		enabled;
	int		red;
	t_color	start_color;
	t_color	end_color;
	t_image	*img;
};

typedef struct s_ctrl	t_ctrl;
struct		s_ctrl
{
	int		mouse;
	int		inside_menu;
	int		last_x;
	int		last_y;
	int		locked;
};

typedef struct s_xpm	t_xpm;
struct		s_xpm
{
	void	*xpm_ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
};

typedef struct s_fract	t_fract;
struct		s_fract
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_menu	*menu;
	t_map	*map;
	t_ctrl	ctrl;
};

typedef pthread_t	t_pthr;
typedef struct s_thread	t_thread;
struct		s_thread
{
	t_pthr	pthr;
	int		id;
	t_fract	*fract;
};

/*
** Mallocs
*/

t_image		*ft_new_image(t_fract *fract, int width, int height);
t_menu		*ft_new_menu(t_fract *fract);
t_fract		*ft_new_fract(void);
t_map		*ft_new_map(void);
void		destroy_fract_exit(t_fract *fract);
void		destroy_image(t_fract *fract, t_image *image);

/*
** Menu
*/

void		ft_init_menu(t_fract *fract);
void		ft_put_menu(t_fract *fract);
void		ft_put_rgb_target(t_menu *menu);
void		ft_put_rgb_selector(t_menu *menu);

/*
** Listeners
*/

int			handle_keypress(int key, t_fract *fract);
int			handle_mouseclicks(int button, int x, int y, t_fract *fract);
int			handle_button_movement(int x, int y, t_fract *fract);

/*
** Render
*/

void		render(t_fract *fract);
void		process_zoom(int x, int y, t_fract *fract, double zoom);
void		handle_movement(int keycode, t_fract *fract);

/*
** Fractals
*/

t_pix		process_mandelbrot(double x, double y, t_map *map);
t_pix		process_julia(double x, double y, t_map *map);
t_pix		process_burning_ship(double x, double y, t_map *map);

/*
** Errors
*/

void		exit_error(char *message);
void		exit_error_destroy(char *message, t_fract *fract);

/*
** Colors
*/

int			ft_rgb_to_int(int r, int g, int b);
int			ft_color_to_int(t_color color);
t_color		ft_rgb_to_color(int r, int g, int b);
t_color		ft_int_to_color(int rgb);
t_color		ft_color_lerp(t_color start, t_color end, double percent);
int			color_for(t_fract *fract, float percent);

/*
** Draw
*/

void		ft_img_put_pixel(t_image *image, int x, int y, int color);
void		ft_draw_edges(t_image *image, t_vec2d start, t_vec2d end,
		int color);
void		ft_draw_square(t_image *image, t_vec2d start, t_vec2d end,
		int color);

/*
** Utils
*/

t_vec2d		to_vec2d(int x, int y);
int			check_map(t_fract *fract);

/*
** Xpm
*/

void		ft_put_xpm_file_to_image(t_fract *fract, char *file, t_image *image,
		t_vec2d pos);

#endif
