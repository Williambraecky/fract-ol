/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:33:14 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/18 14:43:24 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_pix	process_multijulia(double zx, double zy, t_map *map)
{
	int		iterations;
	double	zx2;
	double	zy2;
	double	tmp;
	int		n = map->julia_n;

	iterations = 0;
	zx2 = zx * zx;
	zy2 = zy * zy;
	while (iterations < map->max_iter && (zx2 + zy2) < 32.0)
	{
		tmp = pow((zx * zx + zy * zy), (n / 2)) * cos(n * atan2(zy, zx))
			+ map->real;
		zy = pow((zx * zx + zy * zy), (n / 2)) * sin(n * atan2(zy, zx))
			+ map->imaginary;
		zx = tmp;
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

t_pix	process_julia(double zx, double zy, t_map *map)
{
	int		iterations;
	double	zx2;
	double	zy2;

	iterations = 0;
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
