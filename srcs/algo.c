/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:33:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/14 23:27:08 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//
// void multijulia(t_mlx *fractal, long zoom, long iterations_max, int n)
// {
// 	double cY, cX;
// 	cX = ORIGINALJULIAX;
// 	cY = ORIGINALJULIAY;
// 	double moveX = 0, moveY = 0;
// 	double zx, zy;
//
// 	for (int x = 0; x < DRAW_W; x++)
// 	{
// 		for (int y = 0; y < WIN_H; y++)
// 		{
// 			zx = 1.5 * (x - DRAW_W / 2) / (0.5 * zoom/2 * DRAW_W) + moveX;
// 			zy = (y - WIN_H / 2) / (0.5 * zoom/2 * WIN_H) + moveY;
// 			float i = 0;
// 			while (zx * zx + zy * zy < 4 && i < iterations_max)
// 			{
// 				double tmp = ft_pow((zx * zx + zy * zy), (n / 2)) * cos(n * atan2(zy, zx)) + cX;
// 			    zy = ft_pow((zx * zx + zy * zy), (n / 2)) * sin(n * atan2(zy, zx)) + cY;
// 			    zx = tmp;
// 				// double tmp = zx * zx - zy * zy + cX;
// 				// zy = 2.0 * zx * zy + cY;
// 				// zx = tmp;
// 				i++;
// 			}
// 			if (i == iterations_max)
// 				put_pixel_img(fractal, (t_point){x, y}, 0xFFFFFF);
// 			else
// 			{
// 				if (i * 100 / iterations_max < 50)
// 					put_pixel_img(fractal, (t_point){x, y},
// 						rgb2dec(i*255/(iterations_max*0.75), 0, i*255/(iterations_max*0.75)));
// 				else
// 					put_pixel_img(fractal, (t_point){x, y},
// 						rgb2dec(255, i*255/iterations_max, 0));
// 			}
// 		}
// 	}
// }

t_pix	process_multijulia(double x, double y, t_map *map)
{
	int		iterations;
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;
	int		n = map->julia_n;

	iterations = 0;
	zx = x;
	zy = y;
	zx2 = zx * zx;
	zy2 = zy * zy;
	while (iterations < map->max_iter && (zx2 + zy2) < 32.0)
	{
		double tmp = pow((zx * zx + zy * zy), (n / 2)) * cos(n * atan2(zy, zx))
			+ map->real;
		zy = pow((zx * zx + zy * zy), (n / 2)) * sin(n * atan2(zy, zx))
			+ map->imaginary;
		zx = tmp;
		// zy = 2 * zx * zy + map->imaginary;
		// zx = zx2 - zy2 + map->real;
		zx2 = zx * zx;
		zy2 = zy * zy;
		iterations++;
	}
	return ((t_pix){.iterations = iterations, .c = (zx2 + zy2)});
}

/*
** Process each points mapped as x = lerp(-2, 1, ilerp(0, width, pix_x))
** and y = lerp(-1, 1, ilerp(0, height, pix_y)) after applying zoom and movement
** Returns the number of iterations for said pixel and current imaginary number
*/

t_pix	process_mandelbrot(double x, double y, t_map *map)
{
	int		iterations;
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;

	iterations = 0;
	zx = 0;
	zy = 0;
	zx2 = zx * zx;
	zy2 = zy * zy;
	while (iterations < map->max_iter && (zx2 + zy2) < 256.0)
	{
		zy = 2 * zx * zy + y;
		zx = zx2 - zy2 + x;
		zx2 = zx * zx;
		zy2 = zy * zy;
		iterations++;
	}
	return ((t_pix){.iterations = iterations, .c = (zx2 + zy2)});
}

t_pix	process_julia(double x, double y, t_map *map)
{
	int		iterations;
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;

	iterations = 0;
	zx = x;
	zy = y;
	zx2 = zx * zx;
	zy2 = zy * zy;
	while (iterations < map->max_iter && (zx2 + zy2) < 32.0)
	{
		zy = 2 * zx * zy + map->imaginary;
		zx = zx2 - zy2 + map->real;
		zx2 = zx * zx;
		zy2 = zy * zy;
		iterations++;
	}
	return ((t_pix){.iterations = iterations, .c = (zx2 + zy2)});
}

t_pix	process_burning_ship(double x, double y, t_map *map)
{
	int		iterations;
	double	zx;
	double	zy;
	double	zx2;
	double	zy2;

	iterations = 0;
	zx = x;
	zy = y;
	zx2 = zx * zx;
	zy2 = zy * zy;
	while (iterations < map->max_iter && (zx2 + zy2) < 256.0)
	{
		zy = fabs(2 * zx * zy) + y;
		zx = fabs(zx2 - zy2 + x);
		zx2 = zx * zx;
		zy2 = zy * zy;
		iterations++;
	}
	return ((t_pix){.iterations = iterations, .c = (zx2 + zy2)});
}
