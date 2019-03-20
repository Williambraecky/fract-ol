/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:02:48 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/18 14:45:22 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_img_put_pixel(t_image *image, int x, int y, int color)
{
	if (x < 0 || x >= image->width || y < 0 || y >= image->height)
		return ;
	image->data[y * image->width + x] = color;
}

/*
** Draws vertical line
*/

void	ft_draw_vert(t_image *image, t_vec2d start, int y_end, int color)
{
	if (y_end < start.y)
		ft_swapint(&y_end, &(start.y));
	while (start.y <= y_end)
		ft_img_put_pixel(image, start.x, start.y++, color);
}

/*
** Draws horizontal line
*/

void	ft_draw_hor(t_image *image, t_vec2d start, int x_end, int color)
{
	if (x_end < start.x)
		ft_swapint(&x_end, &(start.x));
	while (start.x <= x_end)
		ft_img_put_pixel(image, start.x++, start.y, color);
}

void	ft_draw_edges(t_image *image, t_vec2d start, t_vec2d end,
		int color)
{
	ft_draw_hor(image, start, end.x, color);
	ft_draw_hor(image, end, start.x, color);
	ft_draw_vert(image, start, end.y, color);
	ft_draw_vert(image, end, start.y, color);
}

void	ft_draw_square(t_image *image, t_vec2d start, t_vec2d end,
		int color)
{
	int x;
	int y;

	y = start.y;
	while (y <= end.y)
	{
		x = start.x;
		while (x <= end.x)
		{
			ft_img_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}
