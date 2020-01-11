/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:54:20 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/11 13:01:21 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	ft_init(t_env *env)
{
	if (env->map.player == 'N')
	{
		env->dir.x = 0;
		env->dir.y = -1;
		env->plane.x = -0.80;
		env->plane.y = 0;
	}
	if (env->map.player == 'S')
	{
		env->dir.x = 0;
		env->dir.y = 1;
		env->plane.x = 0.80;
		env->plane.y = 0;
	}
	if (env->map.player == 'E')
	{
		env->dir.x = 1;
		env->dir.y = 0;
		env->plane.x = 0;
		env->plane.y = -0.80;
	}
	if (env->map.player == 'W')
	{
		env->dir.x = -1;
		env->dir.y = 0;
		env->plane.x = 0;
		env->plane.y = 0.80;
	}


	env->pos.x += 0.5;
	env->pos.y += 0.5;
	env->speed = 0.1;
	env->up = 0;
	env->down = 0;
	env->left = 0;
	env->right = 0;
	env->strafl = 0;
	env->strafr = 0;
	env->tex_x = 0;
	env->tex_y = 0;
	env->step_tex = 0;
	env->tex_pos = 0;
	env->flag_save = 0;

	//suppr si pas necessaire
	env->sp.spcamx = 0;
	env->sp.spcamy = 0;
	env->sp.transx = 0;
	env->sp.transy = 0;
	env->sp.spriteScreenX = 0;
	env->sp.spriteHeight = 0;
	env->sp.drawStartY = 0;
	env->sp.drawEndY = 0;
	env->sp.spriteWidth = 0;
	env->sp.drawStartX = 0;
	env->sp.drawEndX = 0;



	//init xpm
	if((env->tex1 = ft_new_tex(env, env->data.NO)) == NULL)
		return (IMG_FAIL);
	if((env->tex2 = ft_new_tex(env, env->data.SO)) == NULL)
		return (IMG_FAIL);
	if((env->tex3 = ft_new_tex(env, env->data.EA)) == NULL)
		return (IMG_FAIL);
	if((env->tex4 = ft_new_tex(env, env->data.WE)) == NULL)
		return (IMG_FAIL);
	if((env->sprite = ft_new_tex(env, env->data.S)) == NULL)
		return (IMG_FAIL);
	return (1);
}


int	init_env(t_env *env)
{
	int i;
	char **tab;

	i = 0;
	while (!ft_isdigit(env->data.R[i]))
		i++;
	if(!(tab = ft_split(env->data.R + i, ' ')))
		return (MALLOC_FAIL);
	env->width = ft_atoi(tab[0]);
	env->height = ft_atoi(tab[1]);
	ft_tabdel((void **)tab); //attention possible leak ici avec mon split, verifier mon tabdel
	if (!env->width || !env->height) //autre chose a verifier quand a la resolution? 
	//Si la taille de fenêtre demandée dans la map est plus grande que celle de l’écran, la taille de fenêtre doit être celle de l’écran.
	{
		ft_putstr("Wrong resolution");
		return (WRONG_INPUT);
	}
	env->mlx_ptr =  mlx_init();
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->width, env->height, "Cub3D"); //idem

	if((env->img = ft_new_image(env, env->width, env->height)) == NULL)
		return (IMG_FAIL);
	ft_init(env);
	return (SUCCESS);

}
