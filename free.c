/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 19:26:33 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 19:30:22 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_tex(t_env *env, t_tex *tex)
{
	if (tex)
	{
		mlx_destroy_image(env->mlx_ptr, tex->tex_ptr);
		free(tex);
		tex = NULL;
	}
}

void	ft_free_img(t_env *env)
{
	if (env->img)
	{
		mlx_destroy_image(env->mlx_ptr, env->img->img_ptr);
		free(env->img);
		env->img = NULL;
	}
}

void	ft_free_tabs(t_env *env)
{
	if (env->zbuffer)
		free(env->zbuffer);
	if (env->map.tab_map)
		ft_tabdel((void *)env->map.tab_map);
	if (env->data.R)
		free(env->data.R);
	if (env->data.NO)
		free(env->data.NO);
	if (env->data.SO)
		free(env->data.SO);
	if (env->data.WE)
		free(env->data.WE);
	if (env->data.EA)
		free(env->data.EA);
	if (env->data.F)
		free(env->data.F);
	if (env->data.C)
		free(env->data.C);
	if (env->data.SP)
		free(env->data.SP);
}
