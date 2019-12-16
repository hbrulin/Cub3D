/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:03:01 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 14:07:22 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_put_pixel(t_img *img, unsigned int color, int p_x, int p_y)
{
	//verifier avant que le pixel n'est pas en dehors de l'img 
	img->img_data[p_y * img->height + p_x] = color;
}

void	draw(t_env *env, t_img *img)
{
	// a revoir en passant p_x et p_y en argument
	int p_x;
	int p_y;
	unsigned int color;

	color = mlx_get_color_value (env->mlx_ptr, rgb_to_hex(255, 255, 255));

	//si la window n'est pas carre, ne va pas jusqua la fin, pourquoi?
	p_y = -1;
	while  (++p_y < img->height) 
	{
		p_x = -1;
		while (++p_x < img->width)
			ft_put_pixel(img, color, p_x, p_y);
	}
}

void	ft_new_image(t_env *env)
{
	t_img img; //y a til une seule image pour tout le programme, comment ca marche

	img.img_ptr = mlx_new_image (env->mlx_ptr, env->width, env->height);

	//ici je caste en int pour que ca puisse stocker la couleur
    img.img_data = (int *)mlx_get_data_addr (img.img_ptr, &img.bpp, &img.size_line, &img.endian);
	//img.bpp /= 8; //necessaire sans le decalage de bits?
	img.width = env->width;
	img.height = env->height;
	draw(env, &img);

	mlx_put_image_to_window (env->mlx_ptr, env->win_ptr, img.img_ptr, 0, 0);

	//ne pas oublier de free, destroy image
}
