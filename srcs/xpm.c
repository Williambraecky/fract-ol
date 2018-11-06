/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 12:12:34 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/06 11:35:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_xpm	*ft_xpm_file_to_xpm_wrap(t_fract *fract, char *file)
{
	t_xpm	*xpm;

	if (!(xpm = (t_xpm *)ft_memalloc(sizeof(t_xpm))))
		return (NULL);
	xpm->xpm_ptr = mlx_xpm_file_to_image(fract->mlx_ptr, file, &(xpm->width),
			&(xpm->height));
	if (xpm->xpm_ptr == NULL)
	{
		free(xpm);
		return (NULL);
	}
	xpm->data = mlx_get_data_addr(xpm->xpm_ptr, &(xpm->bpp), &(xpm->size_line),
			&(xpm->endian));
	xpm->bpp /= 8;
	return (xpm);
}

static int		ft_xpm_get_color(t_xpm *xpm, int x, int y)
{
	return (*(int *)(xpm->data + (y * xpm->width + x) * xpm->bpp));
}

void			ft_put_xpm_file_to_image(t_fract *fract, char *file,
	t_image *image, t_vec2d pos)
{
	t_xpm	*xpm;
	int		x;
	int		y;
	int		color;

	if (file == NULL || !(xpm = ft_xpm_file_to_xpm_wrap(fract, file)))
		return ;
	y = 0;
	while (y < xpm->height)
	{
		x = 0;
		while (x < xpm->width)
		{
			color = ft_xpm_get_color(xpm, x, y);
			if (color != TRANSPARENT)
				ft_img_put_pixel(image, x + (int)pos.x, y + (int)pos.y,
					ft_xpm_get_color(xpm, x, y));
			x++;
		}
		y++;
	}
	mlx_destroy_image(fract->mlx_ptr, xpm->xpm_ptr);
	free(xpm);
}
