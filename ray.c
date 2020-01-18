/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:58:55 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 11:47:51 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"

void	ft_init_ray(t_env *env, int x)
{
	env->rc.camera = 2 * x / (double)(env->width) - 1;
	env->rc.rpos.x = env->pos.x;
	env->rc.rpos.y = env->pos.y;
	env->rc.rdir.x = env->rc.dir.x + env->rc.plane.x * env->rc.camera;
	env->rc.rdir.y = env->rc.dir.y + env->rc.plane.y * env->rc.camera;
	env->rc.rmap.x = (int)env->rc.rpos.x;
	env->rc.rmap.y = (int)env->rc.rpos.y;
	env->rc.rdisd.x = sqrt(1 + (env->rc.rdir.y * env->rc.rdir.y) / (env->rc.rdir.x * env->rc.rdir.x));
	env->rc.rdisd.y = sqrt(1 + (env->rc.rdir.x * env->rc.rdir.x) / (env->rc.rdir.y * env->rc.rdir.y));
	env->rc.hit = 0;
}

void	ft_direction_ray(t_env *env)
{
	if (env->rc.rdir.x < 0)
	{
		env->rc.step.x = -1;
		env->rc.rdist.x = (env->rc.rpos.x - env->rc.rmap.x) * env->rc.rdisd.x;
	}
	else
	{
		env->rc.step.x = 1;
		env->rc.rdist.x = (env->rc.rmap.x + 1.0 - env->rc.rpos.x) * env->rc.rdisd.x;
	}
	if (env->rc.rdir.y < 0)
	{
		env->rc.step.y = -1;
		env->rc.rdist.y = (env->rc.rpos.y - env->rc.rmap.y) * env->rc.rdisd.y;
	}
	else
	{
		env->rc.step.y = 1;
		env->rc.rdist.y = (env->rc.rmap.y + 1.0 - env->rc.rpos.y) * env->rc.rdisd.y;
	}
}

void	ft_hit_ray(t_env *env)
{
	while (env->rc.hit == 0)
	{
		if (env->rc.rdist.x < env->rc.rdist.y)
		{
			env->rc.rdist.x += env->rc.rdisd.x;
			env->rc.rmap.x += env->rc.step.x;
			env->rc.wall = 0;
		}
		else
		{
			env->rc.rdist.y += env->rc.rdisd.y;
			env->rc.rmap.y += env->rc.step.y;
			env->rc.wall = 1;
		}
		if (env->map.tab_map[env->rc.rmap.y][env->rc.rmap.x] != '0' && env->map.tab_map[env->rc.rmap.y][env->rc.rmap.x] != '2' && env->map.tab_map[env->rc.rmap.y][env->rc.rmap.x] != 'E' && env->map.tab_map[env->rc.rmap.y][env->rc.rmap.x] != 'N' && env->map.tab_map[env->rc.rmap.y][env->rc.rmap.x] != 'S' && env->map.tab_map[env->rc.rmap.y][env->rc.rmap.x] != 'W')
			env->rc.hit = 1;
	}
}

void	ft_size_ray(t_env *env)
{
	if (env->rc.wall == 0)
		env->rc.dist = fabs((env->rc.rmap.x - env->rc.rpos.x
					+ (1 - env->rc.step.x) / 2) / env->rc.rdir.x);
	else
		env->rc.dist = fabs((env->rc.rmap.y - env->rc.rpos.y
					+ (1 - env->rc.step.y) / 2) / env->rc.rdir.y);
	env->rc.rh = fabs((env->height / env->rc.dist));
	env->rc.wstart = (-1 * (env->rc.rh)) / 2 + env->height / 2;
	if (env->rc.wstart < 0)
		env->rc.wstart = 0;
	env->rc.wend = env->rc.rh / 2 + env->height / 2;
	if (env->rc.wend >= env->height)
		env->rc.wend = env->height - 1;

///textures

	double wallx;
	if (env->rc.wall == 0)
		wallx = env->rc.rpos.y + env->rc.dist * env->rc.rdir.y;
	else
		wallx = env->rc.rpos.x + env->rc.dist * env->rc.rdir.x;
	wallx -= (int)wallx;
	env->rc.tex.x = (int)(wallx * 64);
	if (env->rc.wall == 0 && env->rc.rdir.x > 0)
		env->rc.tex.x = 64 - env->rc.tex.x - 1;
	else if (env->rc.wall == 1 && env->rc.rdir.x < 0)
		env->rc.tex.x = 64 - env->rc.tex.x - 1;
	env->rc.step_tex = 1.0 * 64 / env->rc.rh;
	env->rc.tex_pos = (env->rc.wstart -env->height / 2 + env->rc.rh / 2) * env->rc.step_tex;
}
