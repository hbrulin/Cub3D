/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:54:20 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/07 16:32:56 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

/*void	init_angle(t_env *env)
{
	if (env->map.player == 'N')
		env->pos.angle_d = 90;
	else if (env->map.player == 'S')
		env->pos.angle_d = 270;
	else if (env->map.player == 'E')
		env->pos.angle_d = 0;
	else if (env->map.player == 'W')
		env->pos.angle_d = 180;

	env->plane.x = 0;
	env->plane.y = 1; 
}*/

void	ft_init(t_env *env)
{
	env->pos.x += 0.5;
	env->pos.y += 0.5;
	//a initialiser differemment selon qu'on part de l'est ou de l'ouest
	env->dir.x = 1;
	env->dir.y = 0;
	env->plane.x = 0;
	env->plane.y = -0.80;
	env->speed = 0.1;

//peut etre init differemment selon la position de base du player


	//voir apres pour texture
	//env->sky.im = mlx_xpm_file_to_image(e->mlx, SKY, &win_x, &win_y);
	//env->sky.imc = mlx_get_data_addr(e->sky.im, &e->sky.bpp, &e->sky.imlen,
			//&e->sky.endi)
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
	//init_angle(env);
	env->mlx_ptr =  mlx_init();
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->width, env->height, "Cub3D"); //idem

	if((env->img = ft_new_image(env, env->width, env->height)) == NULL)
		return (IMG_FAIL);
	//fill_floor_ceiling(&env, &data);
	ft_init(env);

	return (SUCCESS);

	//ou faut-il free les pointeurs/destroy window? en cas d'event
}
