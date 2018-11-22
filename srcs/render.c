/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:35:47 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/22 22:56:33 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	process_zoom(int x, int y, t_fract *fract, double zoom)
{
	double	mx;
	double	my;

	if (fract->menu->enabled)
		x -= MENU_WIDTH;
	mx = ft_lerp(-2.5, 2.5, (double)x / (double)fract->map->image->width)
	* fract->map->zoom;
	my = ft_lerp(-1.5, 1.5, (double)y / (double)fract->map->image->height)
	* fract->map->zoom;
	fract->map->x_offset -= mx * zoom;
	fract->map->y_offset -= my * zoom;
	if (zoom > 0)
		fract->map->zoom *= 1.05;
	else
		fract->map->zoom *= 0.95;
}

/*
** Returns the color of the pixel
** TODO: Adapt for other fractals
*/

int		pixel_process(t_fract *fract, t_image *img, int x, int y)
{
	t_pix	pix;
	double	i;
	double	zn;
	double	nu;

	pix = fract->map->processor(
		ft_lerp(-2.5, 2.5, (double)x / (double)img->width) * fract->map->zoom +
		fract->map->x_offset,
		ft_lerp(-1.5, 1.5, (double)y / (double)img->height) * fract->map->zoom +
		fract->map->y_offset,
		fract->map);
	if (pix.iterations == fract->map->max_iter)
		return (0);
	if (fract->map->smooth)
	{
		zn = log(pix.c * pix.c + pix.iterations * pix.iterations) / 2.0f;
		nu = log(zn / log(2)) / log(2);
		i = pix.iterations + 1 - nu;
		if (i < 0)
			i = 0;
	}
	else
		i = (double)pix.iterations;
	return (color_for(fract, i / (double) fract->map->max_iter).color);
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
