/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:03:01 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/07 16:28:24 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_put_pixel(t_img *img, unsigned int color, int p_x, int p_y)
{
	if (p_y >= img->height || p_x >= img->width || p_x < 0 || p_y < 0)
		return ;
	//verifier avant que le pixel n'est pas en dehors de l'img 
	img->img_data[p_y * img->width + p_x] = color;
	//ft_putchar_fd('K', 1);
}
//v2 si mon histoire de color ne marche pas
/*void	ft_put_pixel_color_fix(t_img *img, unsigned int color, int p_x, int p_y)
{
	int *tmp;
	if (p_y >= img->height || p_x >= img->width || p_x < 0 || p_y < 0)
		return ;
	tmp = (int *)&img->img_data[(p_y * img->size_line) + (p_x * (img->bpp / 8))];
	*tmp = color;
}*/

static void	ft_disp_col(t_env *env, int x)
{
	int	y;

	t_color color_floor;
	t_color color_ceiling;
	get_color(env, &color_floor, &color_ceiling);
	y = 0;
	while (y < env->wstart) // ou est-ce initialise???
		ft_put_pixel(env->img, color_ceiling.all, x, y++);
	while (y >= env->wstart && y <= env->wend) // ou est-ce initialise???
		ft_put_pixel(env->img, env->color, x, y++);
	while (y < env->height)
		ft_put_pixel(env->img, color_floor.all, x, y++);
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
		//changer avec textures, comprendre ca
		if (env->wall == 0)
			env->color = (env->step.x < 0 ? COLOR_NORTH : COLOR_SOUTH);
		else
			env->color = (env->step.y > 0 ? COLOR_EAST : COLOR_WEST);
		ft_disp_col(env, x++);
	}
}

t_img	*ft_new_image(t_env *env, int width, int height)
{
	t_img *img; //y a til une seule image pour tout le programme, comment ca marche
	//comment verif si tout ca renvoie null
	if (!(img = malloc(sizeof(t_img))))
		return (NULL);
	img->img_ptr = mlx_new_image (env->mlx_ptr, width, height);
	//ici je caste en int pour que ca puisse stocker la couleur
    img->img_data = (int *)mlx_get_data_addr(img->img_ptr, &img->bpp, &img->size_line, &img->endian);
	img->width = width;
	img->height = height;
	return (img);
	//ne pas oublier de free, destroy image
}
