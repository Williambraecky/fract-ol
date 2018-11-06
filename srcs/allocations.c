/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 16:36:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/06 11:34:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_menu		*ft_new_menu(t_fract *fract)
{
	t_menu	*menu;

	if (!(menu = ft_memalloc(sizeof(*menu))))
		return (NULL);
	menu->img = ft_new_image(fract, MENU_WIDTH, WIN_HEIGHT);
	menu->enabled = 1;
	menu->start_color = ft_int_to_color(COLOR_WHITE);
	menu->end_color = ft_int_to_color(COLOR_RED);
	return (menu);
}

t_image		*ft_new_image(t_fract *fract, int width, int height)
{
	t_image		*img;

	if (!(img = ft_memalloc(sizeof(t_image))))
		return (NULL);
	img->img_ptr = mlx_new_image(fract->mlx_ptr, width, height);
	if (img->img_ptr == NULL)
		exit_error("Could not allocate enough memory");
	img->data = mlx_get_data_addr(img->img_ptr,
			&(img->bpp), &(img->size_line), &(img->endian));
	if (!(img->points = malloc(sizeof(int) * (width * height))))
		exit_error("Could not allocate enough memory");
	img->bpp /= 8;
	img->width = width;
	img->height = height;
	return (img);
}

t_fract		*ft_new_fract(void)
{
	t_fract	*fract;

	if (!(fract = ft_memalloc(sizeof(t_fract))))
		return (NULL);
	return (fract);
}

t_map		*ft_new_map(void)
{
	t_map	*map;

	if (!(map = ft_memalloc(sizeof(*map))))
		return (NULL);
	return (map);
}
