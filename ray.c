/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:58:55 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/13 17:43:56 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"

void	ft_init_ray(t_env *env, int x)
{
	env->camera = 2 * x / (double)(env->height) - 1;
	env->rpos.x = env->pos.x;
	env->rpos.y = env->pos.y;
	env->rdir.x = env->dir.x + env->plane.x * env->camera;
	env->rdir.y = env->dir.y + env->plane.y * env->camera;
	env->rmap_x = (int)env->rpos.x;
	env->rmap_y = (int)env->rpos.y;
	env->rdisd.x = sqrt(1 + (env->rdir.y * env->rdir.y) / (env->rdir.x * env->rdir.x));
	env->rdisd.y = sqrt(1 + (env->rdir.x * env->rdir.x) / (env->rdir.y * env->rdir.y));
	env->hit = 0;
}

void	ft_direction_ray(t_env *env)
{
	if (env->rdir.x < 0)
	{
		env->step.x = -1;
		env->rdist.x = (env->rpos.x - env->rmap_x) * env->rdisd.x;
	}
	else
	{
		env->step.x = 1;
		env->rdist.x = (env->rmap_x + 1.0 - env->rpos.x) * env->rdisd.x;
	}
	if (env->rdir.y < 0)
	{
		env->step.y = -1;
		env->rdist.y = (env->rpos.y - env->rmap_y) * env->rdisd.y;
	}
	else
	{
		env->step.y = 1;
		env->rdist.y = (env->rmap_y + 1.0 - env->rpos.y) * env->rdisd.y;
	}
}

void	ft_hit_ray(t_env *env)
{
	while (env->hit == 0)
	{
		if (env->rdist.x < env->rdist.y)
		{
			env->rdist.x += env->rdisd.x;
			env->rmap_x += env->step.x;
			env->wall = 0;
		}
		else
		{
			env->rdist.y += env->rdisd.y;
			env->rmap_y += env->step.y;
			env->wall = 1;
		}
		if (env->map.tab_map[env->rmap_y][env->rmap_x] == '1')
			env->hit = 1;
	}
}

void	ft_size_ray(t_env *env)
{
	//double dist;

	if (env->wall == 0)
		env->dist = fabs((env->rmap_x - env->rpos.x
					+ (1 - env->step.x) / 2) / env->rdir.x);
	else
		env->dist = fabs((env->rmap_y - env->rpos.y
					+ (1 - env->step.y) / 2) / env->rdir.y);
	env->rh = fabs((env->height / env->dist));
	env->wstart = (-1.0 * (env->rh)) / 2.0 + env->height / 2.0;
	if (env->wstart < 0)
		env->wstart = 0;
	env->wend = env->rh / 2 + env->height / 2;
	if (env->wend >= env->height)
		env->wend = env->height - 1;

///textures

	double wallx;
	if (env->wall == 0)
		wallx = env->rpos.y + env->dist * env->rdir.y;
	else
		wallx = env->rpos.x + env->dist * env->rdir.x;
	wallx -= (int)wallx;
	env->tex_x = (int)(wallx * 64);
	if (env->wall == 0 && env->rdir.x > 0)
		env->tex_x = 64 - env->tex_x - 1;
	else if (env->wall == 1 && env->rdir.x < 0)
		env->tex_x = 64 - env->tex_x - 1;
	env->step_tex = 1.0 * 64 / env->rh;
	env->tex_pos = (env->wstart -env->height / 2 + env->rh / 2) * env->step_tex;
}
