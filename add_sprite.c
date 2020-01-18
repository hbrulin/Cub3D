/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:49:48 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 15:50:50 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calc_end_start(t_env *env)
{
	if (env->sp.drawstart_y < 0)
		env->sp.drawstart_y = 0;
	env->sp.drawend_y = env->sp.sprite_height / 2 + env->height / 2;
	if (env->sp.drawend_y >= env->height)
		env->sp.drawend_y = env->height - 1;
	env->sp.sprite_width = abs((int)(env->height / (env->sp.transy)));
	env->sp.drawstart_x = -env->sp.sprite_width / 2 + env->sp.spritescreenx;
	if (env->sp.drawstart_x < 0)
		env->sp.drawstart_x = 0;
	env->sp.drawend_x = env->sp.sprite_width / 2 + env->sp.spritescreenx;
	if (env->sp.drawend_x >= env->width)
		env->sp.drawend_x = env->width - 1;
}

void	ft_sprite_calc(t_env *env, int i)
{
	double inv;

	env->sp.spcamx = env->tab_sprite[env->rc.sp_order[i]].pos_x - env->pos.x;
	env->sp.spcamy = env->tab_sprite[env->rc.sp_order[i]].pos_y - env->pos.y;
	inv = 1.0 / (env->rc.plane.x * env->rc.dir.y - env->rc.dir.x *
		env->rc.plane.y);
	env->sp.transx = inv * (env->rc.dir.y * env->sp.spcamx - env->rc.dir.x *
		env->sp.spcamy);
	env->sp.transy = inv * (-env->rc.plane.y * env->sp.spcamx + env->rc.plane.x
		* env->sp.spcamy);
	env->sp.spritescreenx = (int)((env->width / 2) * (1 + env->sp.transx /
		env->sp.transy));
	env->sp.sprite_height = abs((int)(env->height / env->sp.transy));
	env->sp.drawstart_y = -env->sp.sprite_height / 2 + env->height / 2;
	calc_end_start(env);
}

void	add_sprite_two(t_env *env)
{
	int d;
	int y;

	y = env->sp.drawstart_y;
	if (env->sp.transy > 0 && env->sp.stripe > 0 && env->sp.stripe < env->width
		&& env->sp.transy < env->rc.zbuffer[env->sp.stripe])
	{
		while (y < env->sp.drawend_y)
		{
			d = y * 256 - env->height * 128 + env->sp.sprite_height * 128;
			env->sp.sp_y = ((d * env->sprite->height) / env->sp.sprite_height) /
				256;
			env->color = env->sprite->tex_data[env->sprite->width * env->sp.sp_y
				+ env->sp.sp_x];
			if (env->color != PINK)
				ft_put_pixel(env->img, env->color, env->sp.stripe, y);
			y++;
		}
	}
}

void	add_sprite(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->nb_sprite)
	{
		ft_sprite_calc(env, i);
		env->sp.stripe = env->sp.drawstart_x;
		while (env->sp.stripe < env->sp.drawend_x)
		{
			env->sp.sp_x = (int)(256 * (env->sp.stripe - (-env->sp.sprite_width
			/ 2 + env->sp.spritescreenx)) * env->sprite->width /
			env->sp.sprite_width / 256);
			add_sprite_two(env);
			env->sp.stripe++;
		}
	}
}
