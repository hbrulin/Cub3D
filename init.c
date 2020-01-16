/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:40:42 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 15:41:38 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_var(t_env *env)
{
	env->mlx_ptr = NULL;
	env->win_ptr = NULL;
	env->img = NULL;
	env->tab_sprite = NULL;
	env->tex1 = NULL;
	env->tex2 = NULL;
	env->tex3 = NULL;
	env->tex4 = NULL;
	env->sprite = NULL;
	env->zbuffer = NULL;
	env->sp_order = NULL;
	env->sp_distance = NULL;
	env->map.tab_map = NULL; 
	env->map.list = NULL;
	env->flag_save = 0;
	env->nb_sprite = 0;
	env->speed = 0.1;
	env->move.up = 0;
	env->move.down = 0;
	env->move.left = 0;
	env->move.right = 0;
	env->move.strafl = 0;
	env->move.strafr = 0;
	
	//suppr si pas necessaire
	env->tex.x = 0;
	env->tex.y = 0;
	env->step_tex = 0;
	env->tex_pos = 0;

	//necessaire si 0 sprite?
	/*env->sp.spcamx = 0;
	env->sp.spcamy = 0;
	env->sp.transx = 0;
	env->sp.transy = 0;
	env->sp.spriteScreenX = 0;
	env->sp.spriteHeight = 0;
	env->sp.drawStartY = 0;
	env->sp.drawEndY = 0;
	env->sp.spriteWidth = 0;
	env->sp.drawStartX = 0;
	env->sp.drawEndX = 0;*/
	
	
	//+data set NULL??
}
