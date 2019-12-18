/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_W.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:07:10 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/18 11:50:43 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void reset_W(t_env *env)
{
	if (env->pos.angle_d >= 90 && env->pos.angle_d < 180)
	{
		if (env->pos.flag_angle_right == 1)
			env->map.player = 'E';
		env->map.player = 'W';
	}
	if (env->pos.angle_d >= 180)
	{
		env->map.player = 'S';
	}

	env->pos.angle_d = 0;
	env->pos.angle_rad = 0;
	env->pos.flag_angle_right = 0;
}

void	ft_angle_move_W(t_env *env)
{
	float x;
	float y;

	x = env->pos.x;
	y = env->pos.y;

	if (env->map.player == 'N')
	{
		if (env->pos.angle_d != 0 && env->pos.y >= 0.1 )
		{
			env->pos.y -= (sin(env->pos.angle_d) * 0.1);
			if (env->pos.flag_angle_right == 1 && env->pos.x >= 0.1)
				env->pos.x += (cos(env->pos.angle_d) * 0.1);
			else if (env->pos.x >= 0.1) 
				env->pos.x -= (cos(env->pos.angle_d) * 0.1);
		}
		else if (env->pos.x != 0 && env->pos.y > 0.1)
			env->pos.y -= 0.1;
	}
	if (env->map.player == 'S')
	{
		if (env->pos.angle_d != 0 && env->pos.y >= 0.1)
		{
			env->pos.y += (sin(env->pos.angle_d) * 0.1);
			if (env->pos.flag_angle_right == 1 && env->pos.x >= 0.1)
				env->pos.x -= (cos(env->pos.angle_d) * 0.1);
			else if (env->pos.x >= 0.1) 
				env->pos.x += (cos(env->pos.angle_d) * 0.1);
		}
		else if (env->pos.x != 0 && env->pos.y >= 0.1 )
			env->pos.y += 0.1;
	}
	if (env->map.player == 'W')
	{
		if (env->pos.angle_d != 0 && (env->pos.x >= 0.1))
		{
			env->pos.x -= (sin(env->pos.angle_d) * 0.1);
			if (env->pos.flag_angle_right == 1 && env->pos.y >= 0.1)
				env->pos.y -= (cos(env->pos.angle_d) * 0.1);
			else if (env->pos.y >= 0.1) 
				env->pos.y += (cos(env->pos.angle_d) * 0.1);
		}
		else if (env->pos.x != 0 && env->pos.x >= 0.1 )
			env->pos.x -= 0.1;
	}
	if (env->map.player == 'E')
	{
		if (env->pos.angle_d != 0 && (env->pos.x >= 0.1 && env->pos.y >= 0.1 ))
		{
			env->pos.x += (sin(env->pos.angle_d) * 0.1);
			if (env->pos.flag_angle_right == 1 && env->pos.y >= 0.1)
				env->pos.y += (cos(env->pos.angle_d) * 0.1);
			else if (env->pos.y >= 0.1) 
			env->pos.y -= (cos(env->pos.angle_d) * 0.1);
		}
		else if (env->pos.x != 0 && env->pos.x >= 0.1 )
			env->pos.x += 0.1;
	}
	reset_W(env);
	printf("%f\n", env->pos.x);
	printf("%f\n", env->pos.y);
}
/*
void	ft_y_down(t_env *env)
{
	float x;
	float y;

	x = env->pos.x;
	y = env->pos.y;

	if (env->map.tab_map[y - 1][x] == '0')
	{
		env->map.tab_map[y - 1][x] = env->map.player;
		env->map.tab_map[y][x] = '0';
		env->pos.y = y - 1;
	}
}

void	ft_y_up(t_env *env)
{
	float x;
	float y;

	x = env->pos.x;
	y = env->pos.y;

	if (env->map.tab_map[y + 1][x] == '0')
	{
		env->map.tab_map[y + 1][x] = env->map.player;
		env->map.tab_map[y][x] = '0';
		env->pos.y = y + 1;
	}
}

void	ft_x_down(t_env *env)
{
	float x;
	float y;

	x = env->pos.x;
	y = env->pos.y;

	if (env->map.tab_map[y][x - 1] == '0')
	{
		env->map.tab_map[y][x - 1] = env->map.player;
		env->map.tab_map[y][x] = '0';
		env->pos.x = x - 1;
	}
}

void	ft_x_up(t_env *env)
{
	float x;
	float y;

	x = env->pos.x;
	y = env->pos.y;

	if (env->map.tab_map[y][x + 1] == '0')
	{
		env->map.tab_map[y][x + 1] = env->map.player;
		env->map.tab_map[y][x] = '0';
		env->pos.x = x + 1;
	}
}
*/
