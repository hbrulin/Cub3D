/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 20:54:20 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 15:30:38 by hbrulin          ###   ########.fr       */
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

	if (!(env->zbuffer = malloc(sizeof(double) * env->width)))
		return (MALLOC_FAIL);

	if((env->tex1 = ft_new_tex(env, env->data.NO)) == NULL)
		return (WRONG_TEX);
	if((env->tex2 = ft_new_tex(env, env->data.SO)) == NULL)
		return (WRONG_TEX);
	if((env->tex3 = ft_new_tex(env, env->data.EA)) == NULL)
		return (WRONG_TEX);
	if((env->tex4 = ft_new_tex(env, env->data.WE)) == NULL)
		return (WRONG_TEX);
	if((env->sprite = ft_new_tex(env, env->data.SP)) == NULL)
		return (WRONG_TEX);
	return (SUCCESS);
}


int	init_env(t_env *env)
{
	int i;
	char **tab;
	int error;

	if ((error = get_color(env, &env->color_floor, &env->color_ceiling)) != SUCCESS)
		return(error);

	i = 0;
	while (!ft_isdigit(env->data.R[i]))
		i++;
	if(!(tab = ft_split(env->data.R + i, ' ')))
		return (MALLOC_FAIL);
	if (tab[0])
		env->width = ft_atoi(tab[0]);
	if (tab[1])
		env->height = ft_atoi(tab[1]);
	ft_tabdel((void **)tab); //attention possible leak ici avec mon split, verifier mon tabdel
	if (!env->width || !env->height || env->width < 0 || env->height < 0)
		return (WRONG_INPUT);
	if (env->width > MAX_WIDTH)
		env->width = MAX_WIDTH;
	if (env->height > MAX_HEIGHT)
		env->height = MAX_HEIGHT;
	if(!(env->mlx_ptr =  mlx_init()))
		return(MLX_FAIL);
	//if(!(env->win_ptr = mlx_new_window(env->mlx_ptr, env->width, env->height, "Cub3D")))
	//	return (MLX_FAIL);
	if((env->img = ft_new_image(env, env->width, env->height)) == NULL)
		return (IMG_FAIL);
	if ((error = ft_init(env)) != SUCCESS)
		return(error);
	return (SUCCESS);

}
