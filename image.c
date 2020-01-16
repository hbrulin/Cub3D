/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:03:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 12:23:00 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_put_pixel(t_img *img, unsigned int color, int p_x, int p_y)
{
	if (p_y >= img->height || p_x >= img->width || p_x < 0 || p_y < 0)
		return ;
	img->img_data[p_y * img->width + p_x] = color;
}

static int	ft_disp_col(t_env *env, int x)
{
	int	y;
	//int error;

	y = 0;
	while (y < env->wstart)
		ft_put_pixel(env->img, env->color_ceiling.all, x, y++);
	while (y >= env->wstart && y <= env->wend)
	{
		env->tex_y = (int)env->tex_pos & (64 - 1);
		env->tex_pos += env->step_tex;
		pix_color(env); //definit env->color
		ft_put_pixel(env->img, env->color, x, y);  //juste cette ligne en v avec couleurs sans tex
		y++;
	}
	while (y < env->height)
		ft_put_pixel(env->img, env->color_floor.all, x, y++);
	return (SUCCESS);
}

int		ft_disp_screen(t_env *env)
{
	int	x;
	int error;

	x = 0;
	while (x < env->width)
	{
		ft_init_ray(env, x);
		ft_direction_ray(env);
		ft_hit_ray(env);
		ft_size_ray(env);

		/*
		if (env->wall == 0)
			env->color = (env->step.x < 0 ? COLOR_NORTH : COLOR_SOUTH);
		else
			env->color = (env->step.y > 0 ? COLOR_EAST : COLOR_WEST);*/
		if ((error = ft_disp_col(env, x++)))
			return (error);
		env->zbuffer[x] = env->dist;
	}
	//CONDITIONNER A SEULEMENT SI SPRITE
	init_sprite(env);
	return (SUCCESS);
}

void	pixel_tex(t_tex *tex, t_env *env)
{
		env->color = tex->tex_data[tex->width * env->tex_y + env->tex_x];
}

void	pix_color(t_env *env)
{
	if (env->wall == 0)
	{
		if(env->step.x < 0)
			pixel_tex(env->tex1, env);
		else
			pixel_tex(env->tex2, env);
	}
	else
	{
		if (env->step.y > 0)
			pixel_tex(env->tex3, env);
		else
			pixel_tex(env->tex4, env);
	}
}

t_img	*ft_new_image(t_env *env, int width, int height)
{
	t_img *img; 
	//faut-il free en plus de destroy img?
	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	if(!(img->img_ptr = mlx_new_image (env->mlx_ptr, width, height)))
		return (NULL);
	//ici je caste en int pour que ca puisse stocker la couleur
	if(!(img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian)))
		return (NULL);
	img->width = width;
	img->height = height;
	return (img);
}

t_tex	*ft_new_tex(t_env *env, char *file)
{
	t_tex *tex;
	if (!(tex = malloc(sizeof(t_tex))))
		return (NULL);
	if(!(tex->tex_ptr = mlx_xpm_file_to_image(env->mlx_ptr, file, &tex->width, &tex->height)))
		return (NULL);
	//ici je caste en int pour que ca puisse stocker la couleur
	if(!(tex->tex_data = (int *)mlx_get_data_addr(tex->tex_ptr, &tex->bpp, &tex->size_line, &tex->endian)))
		return (NULL);
	return (tex);
}
