/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 14:32:08 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/25 00:40:02 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_rgb_to_int(int r, int g, int b)
{
	int rgb;

	rgb = 0;
	rgb |= r << 16;
	rgb |= g << 8;
	rgb |= b;
	return (rgb);
}

t_color	ft_rgb_to_color(int r, int g, int b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 0;
	return ((t_color){.rgb = color});
}

t_color	ft_int_to_color(int rgb)
{
	t_rgb color;

	color.r = rgb >> 16 & 0xFF;
	color.g = rgb >> 8 & 0xFF;
	color.b = rgb & 0xFF;
	color.a = 0;
	return ((t_color){.rgb = color});
}

t_color	ft_color_lerp(t_color start, t_color end, double percent)
{
	t_rgb color;

	color.r = start.rgb.r + (double)(end.rgb.r - start.rgb.r) * percent;
	color.g = start.rgb.g + (double)(end.rgb.g - start.rgb.g) * percent;
	color.b = start.rgb.b + (double)(end.rgb.b - start.rgb.b) * percent;
	color.a = 0;
	return ((t_color){.rgb = color});
}
