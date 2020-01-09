/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:03:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/09 12:12:20 by hbrulin          ###   ########.fr       */
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

static void	ft_disp_col(t_env *env, int x)
{
	int	y;

	t_color color_floor;
	t_color color_ceiling;
	get_color(env, &color_floor, &color_ceiling);
	y = 0;
	while (y < env->wstart)
		ft_put_pixel(env->img, color_ceiling.all, x, y++);
	while (y >= env->wstart && y <= env->wend)
	{
		env->tex_y = (int)env->tex_pos & (64 - 1);
		env->tex_pos += env->step_tex;
		pix_color(env); //definit env->color
		ft_put_pixel(env->img, env->color, x, y);  //juste cette ligne en v avec couleurs sans tex
		y++;
	}
	while (y < env->height)
		ft_put_pixel(env->img, color_floor.all, x, y++);
	//printf("floor is %i\n", color_floor.all);
}

void		ft_disp_screen(t_env *env)
{
	int	x;

	x = 0;
	while (x < env->width)
	{
		ft_init_ray(env, x);
		ft_direction_ray(env);
		ft_hit_ray(env);
		ft_size_ray(env);
		ft_sprite_calc(env);
		/*
		if (env->wall == 0)
			env->color = (env->step.x < 0 ? COLOR_NORTH : COLOR_SOUTH);
		else
			env->color = (env->step.y > 0 ? COLOR_EAST : COLOR_WEST);*/
		ft_disp_col(env, x++);
		add_sprite(env);
	}
}

void	pixel_tex(t_tex *tex, t_env *env)
{
		env->color = tex->tex_data[tex->width * env->tex_y + env->tex_x];
}

void	add_sprite(t_env *env)
{
	int stripe = env->sp.drawStartX;
	int texX = 0;
	int y = 0;
	int d = 0;
	int texY = 0;
	while(stripe < env->sp.drawEndX)
	{
		texX = (int)(256 * (stripe - (-env->sp.spriteWidth / 2 + env->sp.spriteScreenX)) * env->sprite->width / env->sp.spriteWidth) / 256;
		y= env->sp.drawStartY;
		if (env->sp.transy > 0 && stripe > 0 && stripe < env->width)
		{
			while (y < env->sp.drawEndY)
			{
				d = y * 256 - env->height * 128 + env->sp.spriteHeight * 128;
				texY = ((d * env->sprite->height) / env->sp.spriteHeight) / 256;
				env->color = env->sprite->tex_data[env->sprite->width * texY + texX];
				if(env->color != 9961608) //pour retirer le rose
					ft_put_pixel(env->img, env->color, stripe, y);
				//printf("%i", env->color);
				y++;
			}
		}
		stripe++;
	}

}

void	pix_color(t_env *env)
{
	//int tex_num = 0;
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
	img->img_ptr = mlx_new_image (env->mlx_ptr, width, height);
	//ici je caste en int pour que ca puisse stocker la couleur
    img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
	img->width = width;
	img->height = height;
	return (img);
}

t_tex	*ft_new_tex(t_env *env, char *file)
{
	//printf("%s\n", file);
	t_tex *tex;
	if (!(tex = malloc(sizeof(t_tex))))
		return (NULL);
	tex->tex_ptr = mlx_xpm_file_to_image(env->mlx_ptr, file, &tex->width, &tex->height);
	//printf("%p\n", tex->tex_ptr);
	//ici je caste en int pour que ca puisse stocker la couleur
    tex->tex_data = (int *)mlx_get_data_addr(tex->tex_ptr, &tex->bpp, &tex->size_line, &tex->endian);
	return (tex);

	//ne pas oublier de destroy les img apres
}
