/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 16:09:53 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 19:45:02 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h> //remove

void	fill(t_img *img, unsigned int color)
{
	int p_x;
	int p_y;

	p_x = -1;
	while  (++p_x < img->height) 
	{
		p_y = -1;
		while (++p_y < img->width)
			ft_put_pixel(img, color, p_x, p_y);
	}
}

int		fill_floor_ceiling(t_env *env, t_map *map)
{
	t_color color_floor;
	t_color color_ceiling;
	t_img	*floor;
	t_img 	*ceiling;
	int error;

	if((error = get_rgb(map, &color_floor, &color_ceiling)) != SUCCESS)
		return (error);

	if((floor = ft_new_image(env, env->width, env->height / 2)) == NULL)
		return (IMG_FAIL);
	fill(floor, color_floor.all);
	mlx_put_image_to_window (env->mlx_ptr, env->win_ptr, floor->img_ptr, 0, env->height/2);

	if((ceiling= ft_new_image(env, env->width, env->height / 2)) == NULL)
		return (IMG_FAIL);
	fill(ceiling, color_ceiling.all);
	mlx_put_image_to_window (env->mlx_ptr, env->win_ptr, ceiling->img_ptr, 0, 0);
	return (SUCCESS);
}
