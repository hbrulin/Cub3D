/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:09:53 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/17 17:56:15 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //remove

void	fill(t_env *env, unsigned int color_floor, unsigned int color_ceiling)
{
	int p_x;
	int p_y;

	p_y = -1;

	while  (++p_y <= env->img->height / 2) 
	{
		p_x = -1;
		while (++p_x < env->img->width)
			ft_put_pixel(env->img, color_ceiling, p_x, p_y);
	}

	while  (++p_y < env->img->height) 
	{
		p_x = -1;
		while (++p_x < env->img->width)
			ft_put_pixel(env->img, color_floor, p_x, p_y);
	}
}

int		fill_floor_ceiling(t_env *env, t_data *data)
{
	t_color color_floor;
	t_color color_ceiling;
	int error;

	if((error = get_color(data, &color_floor, &color_ceiling)) != SUCCESS)
		return (error);
	fill(env, color_floor.all, color_ceiling.all);
	mlx_put_image_to_window (env->mlx_ptr, env->win_ptr, env->img->img_ptr, 0, 0);

	return (SUCCESS);
}
