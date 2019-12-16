/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:03:01 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 14:59:27 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_put_pixel(t_img *img, t_color *colors, int p_x, int p_y)
{
	//verifier avant que le pixel n'est pas en dehors de l'img 
	img->img_data[p_y * img->height + p_x] = colors->color;
}

int	draw(t_env *env, t_img *img, t_map *map)
{
	t_color colors;
	int error;

	// a revoir en passant p_x et p_y en argument
	int p_x;
	int p_y;

	if((error = get_rgb(map, &colors)) != SUCCESS)
		return (error);
	
	colors.color = mlx_get_color_value (env->mlx_ptr, rgb_to_hex(colors.r_ceiling, colors.g_ceiling, colors.b_ceiling));

	//si la window n'est pas carre, ne va pas jusqua la fin, pourquoi?
	p_y = -1;
	while  (++p_y < img->height) 
	{
		p_x = -1;
		while (++p_x < img->width)
			ft_put_pixel(img, &colors, p_x, p_y);
	}
	return (SUCCESS);
}

int	ft_new_image(t_env *env, t_map *map)
{
	t_img img; //y a til une seule image pour tout le programme, comment ca marche
	int error;
	//comment verif si tout ca renvoie null
	img.img_ptr = mlx_new_image (env->mlx_ptr, env->width, env->height);

	//ici je caste en int pour que ca puisse stocker la couleur
    img.img_data = (int *)mlx_get_data_addr (img.img_ptr, &img.bpp, &img.size_line, &img.endian);

	img.width = env->width;
	img.height = env->height;
	if ((error = draw(env, &img, map)) != SUCCESS)
		return (error);
	mlx_put_image_to_window (env->mlx_ptr, env->win_ptr, img.img_ptr, 0, 0);
	return (SUCCESS);
	//ne pas oublier de free, destroy image
}
