/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:03:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 11:58:16 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_put_pixel(t_img *img, unsigned int color, int p_x, int p_y)
{
	if (p_y >= img->height || p_x >= img->width || p_x < 0 || p_y < 0)
		return ;
	img->img_data[p_y * img->width + p_x] = color;
}

static int	ft_disp_col(t_env *env, int x)
{
	int	y;

	y = 0;
	while (y < env->rc.wstart)
		ft_put_pixel(env->img, env->color_ceiling.all, x, y++);
	while (y >= env->rc.wstart && y <= env->rc.wend)
	{
		env->rc.tex.y = (int)env->rc.tex_pos & (64 - 1);
		env->rc.tex_pos += env->rc.step_tex;
		pix_color(env);
		ft_put_pixel(env->img, env->color, x, y);
		y++;
	}
	while (y < env->height)
		ft_put_pixel(env->img, env->color_floor.all, x, y++);
	return (SUCCESS);
}

int			ft_disp_screen(t_env *env)
{
	int	x;

	x = 0;
	while (x < env->width)
	{
		ft_init_ray(env, x);
		ft_direction_ray(env);
		ft_hit_ray(env);
		ft_size_ray(env);
		ft_wall_tex(env);
		if ((env->error = ft_disp_col(env, x++)))
			return (env->error);
		env->rc.zbuffer[x] = env->rc.dist;
	}
	if((env->error = init_sprite(env)))
		return(env->error);
	return (SUCCESS);
}
