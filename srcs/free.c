/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:24:31 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/24 23:30:42 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	destroy_image(t_fract *fract, t_image *image)
{
	image->width = 0;
	image->height = 0;
	mlx_destroy_image(fract->mlx_ptr, image->img_ptr);
	free(image);
}

void	destroy_menu(t_fract *fract, t_menu *menu)
{
	if (!menu)
		return ;
	if (menu->img)
		destroy_image(fract, menu->img);
	if (menu->colors)
		ft_memdel((void **)&(menu->colors));
	free(menu);
}

void	destroy_map(t_fract *fract, t_map *map)
{
	if (!map)
		return ;
	if (map->image)
		destroy_image(fract, map->image);
	ft_memdel((void **)&map);
}

void	destroy_fract(t_fract *fract)
{
	if (!fract)
		return ;
	destroy_map(fract, fract->map);
	destroy_menu(fract, fract->menu);
	mlx_destroy_window(fract->mlx_ptr, fract->win_ptr);
	*(fract->count) -= 1;
	ft_memdel((void **)&fract);
}

void	destroy_fract_exit(t_fract *fract)
{
	if (!fract)
		return ;
	destroy_map(fract, fract->map);
	destroy_menu(fract, fract->menu);
	mlx_destroy_window(fract->mlx_ptr, fract->win_ptr);
	*(fract->count) -= 1;
	if (*(fract->count) == 0)
	{
		ft_memdel((void **)&fract);
		exit(0);
	}
	ft_memdel((void **)&fract);
}
