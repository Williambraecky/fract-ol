/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:20:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/25 00:37:35 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_put_menu(t_fract *fract)
{
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr,
			fract->menu->img->img_ptr, 0, 0);
}

t_color		color_for(t_fract *fract, double percent)
{
	t_color	prev_color;
	double	prev_prcnt;
	size_t	i;

	prev_prcnt = 0.0;
	prev_color = fract->menu->start_color;
	i = 0;
	while (i < fract->menu->size)
	{
		if (percent < fract->menu->colors[i].percent)
			return (ft_color_lerp(prev_color, fract->menu->colors[i].color,
				(percent - prev_prcnt) * 1 /
				(fract->menu->colors[i].percent - prev_prcnt)));
		prev_prcnt = fract->menu->colors[i].percent;
		prev_color = fract->menu->colors[i].color;
		i++;
	}
	return (ft_color_lerp(prev_color, fract->menu->end_color,
		(percent - prev_prcnt) * 1 / (1.0 - prev_prcnt)));
}

void		ft_put_rgb_target(t_fract *fract, t_menu *menu)
{
	int		color;
	int		y;
	int		x;

	x = 0;
	while (x < 301)
	{
		y = 0;
		color = color_for(fract, (double)x / 300).color;
		while (y < 25)
		{
			ft_img_put_pixel(menu->img, x + 25, y + 569, color);
			y++;
		}
		x++;
	}
}

void		ft_put_rgb_selector(t_menu *menu)
{
	int	y;
	int	x;

	y = -1;
	while (++y < 256)
	{
		x = -1;
		while (++x < 256)
			ft_img_put_pixel(menu->img,
			x + 25, y + 619, ft_rgb_to_int(menu->red, x, y));
	}
	y = -1;
	while (++y < 256)
	{
		x = -1;
		while (++x < 25)
			ft_img_put_pixel(menu->img,
					x + 301, y + 619, ft_rgb_to_int(y, 0, 0));
	}
}

int			ft_init_menu(t_fract *fract)
{
	if (!(fract->menu = ft_new_menu(fract)))
	{
		ft_printf_fd(2, "Fractol: Menu out of memory\n");
		destroy_fract(fract);
		return (0);
	}
	ft_draw_square(fract->menu->img, to_vec2d(0, 0),
			to_vec2d(MENU_WIDTH, WIN_HEIGHT), MENU_COLOR);
	ft_draw_square(fract->menu->img, to_vec2d(MENU_WIDTH - 3, 0),
			to_vec2d(MENU_WIDTH, WIN_HEIGHT), BORDER_COLOR);
	ft_draw_edges(fract->menu->img, to_vec2d(24, 618),
			to_vec2d(281, 875), BORDER_COLOR);
	ft_draw_edges(fract->menu->img, to_vec2d(300, 618),
			to_vec2d(326, 875), BORDER_COLOR);
	ft_draw_edges(fract->menu->img, to_vec2d(24, 568),
			to_vec2d(326, 594), BORDER_COLOR);
	ft_put_rgb_selector(fract->menu);
	ft_put_rgb_target(fract, fract->menu);
	ft_put_xpm_file_to_image(fract, "wbraeckm_logo.xpm",
			fract->menu->img, to_vec2d(25, 25));
	ft_put_xpm_file_to_image(fract, "logo19.xpm",
			fract->menu->img, to_vec2d(135, 140));
	ft_put_menu(fract);
	return (1);
}
