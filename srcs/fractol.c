/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:46:24 by wbraeckm          #+#    #+#             */
/*   Updated: 2019/03/14 23:35:43 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_fract(t_fract *fract, char *arg)
{
	if (ft_strequ("mandelbrot", arg))
		fract->map->processor = process_mandelbrot;
	else if (ft_strequ("julia", arg))
		fract->map->processor = process_julia;
	else if (ft_strequ("burningship", arg))
		fract->map->processor = process_burning_ship;
	else if (ft_strequ("multijulia", arg))
		fract->map->processor = process_multijulia;
	mlx_key_hook(fract->win_ptr, handle_keypress, fract);
	mlx_mouse_hook(fract->win_ptr, handle_mouseclicks, fract);
	mlx_hook(fract->win_ptr, BUTTONRELEASE, 0, handle_mouseclicks, fract);
	mlx_hook(fract->win_ptr, MOTIONNOTIFY, BUTTON1MOTIONMASK,
		handle_button_movement, fract);
	render(fract);
}

static void	read_args(void *mlx_ptr, int *count, int argc, char **argv)
{
	t_fract	*fract;
	int		i;

	i = 0;
	while (++i < argc)
	{
		if (!fractal_exists(argv[i]) &&
			ft_printf_fd(2, "Fractal %s does not exist.\n", argv[i]))
			continue ;
		if (!(fract = ft_new_fract()) &&
			ft_printf_fd(2, "Fractal %d: Out of memory.\n", i - 1))
			continue ;
		fract->mlx_ptr = mlx_ptr;
		if (!(fract->win_ptr =
			mlx_new_window(fract->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Fractol")))
		{
			destroy_fract(fract);
			continue ;
		}
		fract->count = count;
		if (!ft_init_menu(fract))
			continue ;
		init_fract(fract, argv[i]);
		(*count) += 1;
	}
}

/*
** TODO: Make sure no leaks are possible
** TODO: Implement subpixel logic for smoother zoom and maybe movements
** TODO: Norm everything
** TODO: Optimize multijulia
** TODO: Refactor fractol.h
*/

int			main(int argc, char **argv)
{
	void	*mlx_ptr;
	int		count;

	if (argc < 2)
		exit_error("Usage: ./fractol [mandelbrot|julia|burningship]");
	if (!(mlx_ptr = mlx_init()))
		exit_error("Could not initialize mlx");
	count = 0;
	read_args(mlx_ptr, &count, argc, argv);
	if (count == 0)
		exit_error("No valid fractal.\n\
Usage: ./fractol [mandelbrot|julia|burningship]");
	mlx_loop(mlx_ptr);
	return (0);
}
