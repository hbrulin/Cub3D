/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 15:31:18 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/15 15:33:57 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

//lancer cette fonction dand display
void	ft_sprite_calc(t_env *env)
{
	env->sp.spcamx = env->sp.pos_x - env->pos.x; 
	env->sp.spcamy = env->sp.pos_y - env->pos.y;; 

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
