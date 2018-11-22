/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbraeckm <wbraeckm@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:17:27 by wbraeckm          #+#    #+#             */
/*   Updated: 2018/11/22 22:50:28 by wbraeckm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		reset_colors(t_fract *fract)
{
	ft_memdel((void **)&(fract->menu->colors));
	fract->menu->size = 0;
	ft_put_rgb_target(fract, fract->menu);
}

static int	check_contains(t_fract *fract, t_color color, double percent)
{
	size_t	i;

	i = 0;
	while (i < fract->menu->size)
	{
		if (fract->menu->colors[i].percent == percent)
		{
			fract->menu->colors[i].color = color;
			return (1);
		}
		i++;
	}
	return (0);
}

void		add_color(t_fract *fract, t_color color, double percent)
{
	t_cols	*tmp;
	size_t	i;
	size_t	j;

	if (check_contains(fract, color, percent))
		return ;
	if (!(tmp = ft_memalloc(sizeof(*tmp) * (fract->menu->size + 1))))
	{
		ft_printf_fd(2, "Error: could not realloc color map\n");
		return ;
	}
	i = 0;
	j = 0;
	while (i < fract->menu->size)
	{
		if (fract->menu->colors[i].percent > percent && !j++)
			tmp[i] = (t_cols){.color = color, .percent = percent};
		tmp[i + (j > 0 ? 1 : 0)] = fract->menu->colors[i];
		i++;
	}
	if (!j)
		tmp[i] = (t_cols){.color = color, .percent = percent};
	ft_memdel((void **)&(fract->menu->colors));
	fract->menu->colors = tmp;
	fract->menu->size++;
}
