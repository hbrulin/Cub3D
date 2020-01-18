/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:18 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/18 12:13:45 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>


void	ft_sprite_calc(t_env *env, int i)
{
	env->sp.spcamx = env->tab_sprite[env->rc.sp_order[i]].pos_x - env->pos.x; 
	env->sp.spcamy = env->tab_sprite[env->rc.sp_order[i]].pos_y - env->pos.y;; 

 	double inv = 1.0 / (env->rc.plane.x * env->rc.dir.y - env->rc.dir.x * env->rc.plane.y); //required for correct matrix multiplication

      env->sp.transx = inv * (env->rc.dir.y * env->sp.spcamx - env->rc.dir.x * env->sp.spcamy);
      env->sp.transy = inv * (-env->rc.plane.y * env->sp.spcamx + env->rc.plane.x * env->sp.spcamy); //this is actually the depth inside the screen, that what Z is in 3D

      env->sp.spriteScreenX = (int)((env->width / 2) * (1 + env->sp.transx / env->sp.transy));

	//calculate height of the sprite on screen
      env->sp.spriteHeight = abs((int)(env->height / env->sp.transy)); 
      //calculate lowest and highest pixel to fill in current stripe
      env->sp.drawStartY = -env->sp.spriteHeight / 2 + env->height / 2;
      if(env->sp.drawStartY < 0) 
	  	env->sp.drawStartY = 0;
      env->sp.drawEndY = env->sp.spriteHeight / 2 + env->height / 2;
      if(env->sp.drawEndY >= env->height) 
	  	env->sp.drawEndY = env->height - 1;

      //calculate width of the sprite
      env->sp.spriteWidth = abs( (int) (env->height / (env->sp.transy)));
      env->sp.drawStartX = - env->sp.spriteWidth / 2 + env->sp.spriteScreenX;
      if(env->sp.drawStartX < 0) 
	  	env->sp.drawStartX = 0;
      env->sp.drawEndX = env->sp.spriteWidth / 2 + env->sp.spriteScreenX;
      if(env->sp.drawEndX >= env->width) 
	  	env->sp.drawEndX = env->width - 1;
}

void	add_sprite_two(t_env *env)
{
	int d;
	int y;

	y = env->sp.drawStartY;
	if (env->sp.transy > 0 && env->sp.stripe > 0 && env->sp.stripe < env->width
		&& env->sp.transy < env->rc.zbuffer[env->sp.stripe])
	{
		while (y < env->sp.drawEndY)
		{
			d = y * 256 - env->height * 128 + env->sp.spriteHeight * 128;
			env->sp.sp_y = ((d * env->sprite->height) / env->sp.spriteHeight) /
				256;
			env->color = env->sprite->tex_data[env->sprite->width * env->sp.sp_y
				+ env->sp.sp_x];
			if(env->color != PINK) 
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
		env->sp.stripe = env->sp.drawStartX;
		while(env->sp.stripe < env->sp.drawEndX)
		{
			env->sp.sp_x = (int)(256 * (env->sp.stripe - (-env->sp.spriteWidth /
				2 + env->sp.spriteScreenX)) * env->sprite->width / 
				env->sp.spriteWidth / 256);
			add_sprite_two(env);
			env->sp.stripe++;
		}
	}
}

void	ft_sort(int *order, double *dist, int num)
{
	int		i;
	int		temp;
	double	temp2;

	i = 0;

	while (i < num - 1)
	{
		if (dist[i] < dist[i + 1])
		{
			temp2 = dist[i + 1];
			dist[i + 1] = dist[i];
			dist[i] = temp2;
			temp = order[i + 1];
			order[i + 1] = order[i];
			order[i] = temp;
			i = 0;
		}
		else
			i++;
	}
}

void		ft_order_sprite(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_sprite)
	{
		env->rc.sp_order[i] = i;
		env->rc.sp_distance[i] = ((env->pos.x - env->tab_sprite[i].pos_x) * (env->pos.x - env->tab_sprite[i].pos_x) + (env->pos.y - env->tab_sprite[i].pos_y) * (env->pos.y - env->tab_sprite[i].pos_y));
		i++;
	}
	ft_sort(env->rc.sp_order, env->rc.sp_distance, env->nb_sprite);
	add_sprite(env);
}

void	ft_place_sprite(t_env *env)
{
	int x;
	int y;
	int i;

	i = 0;
	y = 0;
	while (y < env->map.nb_line)
	{
		x = 0;
		while (x < env->map.nb_char)
		{
			if (env->map.tab_map[y][x] == '2')
			{
				env->tab_sprite[i].pos_x = x + 0.5;
				env->tab_sprite[i].pos_y = y + 0.5;
				i++;
			}
			x++;
		}
		y++;
	}
}

int	init_sprite(t_env *env)
{
	int		i;

	i = 0;
	if (!(env->tab_sprite = malloc(sizeof(t_sprite) * env->nb_sprite)))
		return (MALLOC_FAIL);
	if (!(env->rc.sp_order = malloc(sizeof(int) * env->nb_sprite)))
		return (MALLOC_FAIL);
	if (!(env->rc.sp_distance = malloc(sizeof(double) * env->nb_sprite)))
		return (MALLOC_FAIL);
	ft_place_sprite(env);
	ft_order_sprite(env);
	if (env->tab_sprite)
		free(env->tab_sprite);
	if (env->rc.sp_order)
		free(env->rc.sp_order);
	if (env->rc.sp_distance)
		free(env->rc.sp_distance);
	return (SUCCESS);
}
