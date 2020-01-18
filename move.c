/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:07:10 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 13:34:23 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

void	ft_rotate(t_env *env, int advance)
{
	double	dir;
	double	plane;

	dir = env->rc.dir.x;
	plane = env->rc.plane.x;
	env->rc.dir.x = env->rc.dir.x * cos(advance * 0.1)
		- env->rc.dir.y * sin(advance * 0.1);
	env->rc.dir.y = dir * sin(advance * 0.1)
		+ env->rc.dir.y * cos(advance * 0.1);
	env->rc.plane.x = env->rc.plane.x * cos(advance * 0.1)
		- env->rc.plane.y * sin(advance * 0.1);
	env->rc.plane.y = plane * sin(advance * 0.1)
		+ env->rc.plane.y * cos(advance * 0.1);
}

void	up_down(t_env *env)
{
	if (env->move.up == 1)
	{
		if (env->map.tab_map[(int)(env->pos.y)][(int)(env->pos.x + env->rc.dir.x
			* env->rc.speed)] == '0')
			env->pos.x += env->rc.dir.x * env->rc.speed;
		if (env->map.tab_map[(int)(env->pos.y + env->rc.dir.y *
			env->rc.speed)][(int)(env->pos.x)] == '0')
			env->pos.y += env->rc.dir.y * env->rc.speed;
	}
	if (env->move.down == 1)
	{
		if (env->map.tab_map[(int)(env->pos.y)][(int)(env->pos.x - env->rc.dir.x
			* env->rc.speed)] == '0')
			env->pos.x -= env->rc.dir.x * env->rc.speed;
		if (env->map.tab_map[(int)(env->pos.y - env->rc.dir.y *
			env->rc.speed)][(int)(env->pos.x)] == '0')
			env->pos.y -= env->rc.dir.y * env->rc.speed;
	}
}

void	straf(t_env *env)
{
	if (env->move.strafr == 1)
	{
		if (env->map.tab_map[(int)(env->pos.y - env->rc.dir.x *
			env->rc.speed)][(int)(env->pos.x)] == '0')
			env->pos.y += -env->rc.dir.x * env->rc.speed;
		if (env->map.tab_map[(int)(env->pos.y)][(int)(env->pos.x
			+ env->rc.dir.y * env->rc.speed)] == '0')
			env->pos.x += env->rc.dir.y * env->rc.speed;
	}
	if (env->move.strafl == 1)
	{
		if (env->map.tab_map[(int)(env->pos.y + env->rc.dir.x *
			env->rc.speed)][(int)(env->pos.x)] == '0')
			env->pos.y -= -env->rc.dir.x * env->rc.speed;
		if (env->map.tab_map[(int)(env->pos.y)][(int)(env->pos.x -
			env->rc.dir.y * env->rc.speed)] == '0')
			env->pos.x -= env->rc.dir.y * env->rc.speed;
	}
}

void	ft_move(t_env *env)
{
	if (env->move.up == 1 || env->move.down == 1)
		up_down(env);
	if (env->move.strafr == 1 || env->move.strafl == 1)
		straf(env);
	if (env->move.left == 1)
		ft_rotate(env, 1);
	if (env->move.right == 1)
		ft_rotate(env, -1);
}
