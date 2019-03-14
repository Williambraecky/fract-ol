/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:06:21 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/14 23:25:56 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_vec2d	to_vec2d(int x, int y)
{
	t_vec2d	vec;

	vec.x = x;
	vec.y = y;
	return (vec);
}

int		check_map(t_fract *fract)
{
	t_map	*map;
	int		width;

	if (!fract || !fract->map)
		return (0);
	width = fract->menu->enabled ? WIN_WIDTH - MENU_WIDTH : WIN_WIDTH;
	map = fract->map;
	if (map->image == NULL || map->image->width != width)
	{
		if (map->image != NULL)
			destroy_image(fract, map->image);
		map->image = ft_new_image(fract, width, WIN_HEIGHT);
		if (!map->image)
			return (0);
	}
	else
		ft_memset(map->image->data, 0,
				map->image->width * map->image->height * map->image->bpp);
	return (1);
}

void	handle_movement(int keycode, t_fract *fract)
{
	double	m;

	if (keycode == UP_KEY || keycode == DOWN_KEY)
	{
		if (keycode == UP_KEY)
			m = ft_lerp(-1.5, 1.5, 0.51) * fract->map->zoom;
		else
			m = ft_lerp(-1.5, 1.5, 0.49) * fract->map->zoom;
		fract->map->y_offset -= m;
	}
	else
	{
		if (keycode == LEFT_KEY)
			m = ft_lerp(-2.5, 2.5, 0.49) * fract->map->zoom;
		else
			m = ft_lerp(-2.5, 2.5, 0.51) * fract->map->zoom;
		fract->map->x_offset += m;
	}
}

int		fractal_exists(char *str)
{
	if (ft_strequ(str, "mandelbrot") || ft_strequ(str, "julia") ||
		ft_strequ(str, "burningship") || ft_strequ(str, "multijulia"))
		return (1);
	return (0);
}
