/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:54:20 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/18 10:26:08 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	init_env(t_env *env, t_data *data)
{
	int i;
	char **tab;

	i = 0;
	while (!ft_isdigit(data->R[i]))
		i++;
	if(!(tab = ft_split(data->R + i, ' ')))
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
	env->pos.angle_d = 0;
	env->pos.flag_angle_right = 0; //voir si necessaire
	env->mlx_ptr =  mlx_init(); //verif si NULL : comment?
	env->win_ptr = mlx_new_window(env->mlx_ptr, env->width, env->height, "Cub3D"); //idem

	if((env->img = ft_new_image(env, env->width, env->height)) == NULL)
		return (IMG_FAIL);
	
	return (SUCCESS);

	//ou faut-il free les pointeurs/destroy window? en cas d'event
}
