/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:35:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/14 14:54:22 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Returns the color of the pixel
** TODO: use zoom and movement
*/

int		pixel_process(t_fract *fract, t_image *img, int x, int y)
{
	t_pix	pix;
	double i;
	double zn;
	double nu;

	pix = fract->map->processor(
		ft_lerp(-2.5 * fract->map->zoom, 1.5 * fract->map->zoom,
			ft_ilerp(0, img->width, x + fract->map->x_offset)),
		ft_lerp(-1.5 * fract->map->zoom, 1.5 * fract->map->zoom,
			ft_ilerp(0, img->height, y + fract->map->y_offset)),
		fract->map->max_iter);
	if (pix.iterations == fract->map->max_iter)
		return (ft_color_to_int(fract->menu->end_color));
	if (fract->map->smooth)
	{
		zn = log(pix.c * pix.c + pix.iterations * pix.iterations) / 2.0f;
		nu = log(zn / log(2)) / log(2);
		i = pix.iterations + 1 - nu;
		if (i < 0)
			i = 0;
	}
	else
		i = (float)pix.iterations;
	return (ft_color_to_int(ft_color_lerp(fract->menu->end_color,
		fract->menu->start_color,
		i / (float) fract->map->max_iter)));
}

void	*render_partition(void *ptr)
{
	t_thread	*thr;
	t_image		*image;
	int			y;
	int			max_y;
	int			x;

	thr = (t_thread *)ptr;
	image = thr->fract->map->image;
	y = (image->height / NB_THREAD) * thr->id;
	max_y = (image->height / NB_THREAD) * (thr->id + 1);
	while (y < max_y)
	{
		x = 0;
		while (x < image->width)
		{
			ft_img_put_pixel(image, x, y,
				pixel_process(thr->fract, image, x, y));
			x++;
		}
		y++;
	}
	return (NULL);
}

void	put_map(t_fract *fract, t_map *map)
{
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, map->image->img_ptr,
	fract->menu->enabled ? MENU_WIDTH : 0, 0);
}

void	render(t_fract *fract)
{
	t_thread	threads[NB_THREAD];
	int			i;

	if (!fract)
		exit_error("Fract is null");
	if (!check_map(fract))
		exit_error_destroy("could not create image for render", fract);
	i = 0;
	while (i < NB_THREAD)
	{
		threads[i].id = i;
		threads[i].fract = fract;
		if (pthread_create(&(threads[i].pthr), NULL,
		render_partition, &(threads[i])) == -1)
		{
			ft_printf_fd(2, "fractol: Could not create thread\n");
			destroy_fract_exit(fract);
		}
		i++;
	}
	i = 0;
	while (i < NB_THREAD)
		pthread_join(threads[i++].pthr, NULL);
	put_map(fract, fract->map);
}
