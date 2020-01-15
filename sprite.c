/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:18 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/15 18:23:12 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>


void	add_sprite(t_env *env)
{
	int i;
	int stripe;
	int texX = 0;
	int y = 0;
	int d = 0;
	int texY = 0;

	i = -1;
	while (++i < env->nb_sprite)
	{
		ft_sprite_calc(env, i);
		stripe = env->sp.drawStartX;
		while(stripe < env->sp.drawEndX)
		{
			texX = (int)(256 * (stripe - (-env->sp.spriteWidth / 2 + env->sp.spriteScreenX)) * env->sprite->width / env->sp.spriteWidth / 256);
			y= env->sp.drawStartY;
			if (env->sp.transy > 0 && stripe > 0 && stripe < env->width && env->sp.transy < env->zbuffer[stripe])
			{
				while (y < env->sp.drawEndY)
				{
					d = y * 256 - env->height * 128 + env->sp.spriteHeight * 128;
					texY = ((d * env->sprite->height) / env->sp.spriteHeight) / 256;
					env->color = env->sprite->tex_data[env->sprite->width * texY + texX];
					if(env->color != PINK) //ici potentielle condition manquante pour fix pb sprites qui bougent
						ft_put_pixel(env->img, env->color, stripe, y);
					y++;
				}
			}
			stripe++;
		}
	}
}

void	ft_sort(int *order, double *dist, int num)
{
	int		i;
	int		temp;
	double	temp2;
	int		s;

	s = -1;
	i = 0;
	while (++s < num * 4)
	{
		while (i < num - 1)
		{
			if (dist[i] < dist[i + 1])
			{
				temp2 = dist[i + 1];
				dist[i + 1] = dist[i];//(dist[i] < 0 ? fabs(dist[i]) + 2 : dist[i]);
				dist[i] = temp2;//(temp2 < 0 ? fabs(temp2) + 2 : temp2);
				temp = order[i + 1];
				order[i + 1] = order[i];
				order[i] = temp;
				i = 0;
			}
			else
				i++;
		}
	}
}

void		ft_order_sprite(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_sprite)
	{
		env->sp_order[i] = i;
		env->sp_distance[i] = ((env->pos.x - env->tab_sprite[i].pos_x) * (env->pos.x - env->tab_sprite[i].pos_x) + (env->pos.y - env->tab_sprite[i].pos_y) * (env->pos.y - env->tab_sprite[i].pos_y));
		i++;
	}
	ft_sort(env->sp_order, env->sp_distance, env->nb_sprite);
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

void	init_sprite(t_env *env)
{
	int			i;

	i = 0;
	//secu ici system error +leaks
	if (!(env->tab_sprite = malloc(sizeof(t_sprite) * env->nb_sprite)))
		return ;
	if (!(env->sp_order = malloc(sizeof(int) * env->nb_sprite)))
		return ;
	if (!(env->sp_distance = malloc(sizeof(double) * env->nb_sprite)))
		return ;
	ft_place_sprite(env);
	ft_order_sprite(env);
	if (env->tab_sprite)
		free(env->tab_sprite);
	if (env->sp_order)
		free(env->sp_order);
	if (env->sp_distance)
		free(env->sp_distance);
}

void	ft_sprite_calc(t_env *env, int i)
{
	env->sp.spcamx = env->tab_sprite[i].pos_x - env->pos.x; 
	env->sp.spcamy = env->tab_sprite[i].pos_y - env->pos.y;; 

 	double inv = 1.0 / (env->plane.x * env->dir.y - env->dir.x * env->plane.y); //required for correct matrix multiplication

      env->sp.transx = inv * (env->dir.y * env->sp.spcamx - env->dir.x * env->sp.spcamy);
      env->sp.transy = inv * (-env->plane.y * env->sp.spcamx + env->plane.x * env->sp.spcamy); //this is actually the depth inside the screen, that what Z is in 3D

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
