/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:03:01 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/15 11:47:33 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_put_pixel(t_img *img, unsigned int color)
{
	int p_x;
	int p_y;

	// il faut verifier que le pixel n'est pas en dehors de la map
	p_x = 10;
	p_y = 5;

	unsigned char r;
  	unsigned char g;
  	unsigned char b;
	
	r = (color & 0xFF00000) >> 16;
  	g = (color & 0xFF000) >> 8;
  	b = (color & 0xFF);

	img->img_data[(p_y * img->size_line) * p_x + img->bpp] = b;
	img->img_data[(p_y * img->size_line) * p_x + img->bpp + 1] = g; 
	img->img_data[(p_y * img->size_line) * p_x + img->bpp + 2] = r;

}

void	ft_new_image(t_env *env)
{
	t_img img; //y a til une seule image pour tout le programme, comment ca marche
	unsigned int color;
	
	img.img_ptr = mlx_new_image (env->mlx_ptr, env->width, env->height );

    img.img_data = mlx_get_data_addr (img.img_ptr, &img.bpp, &img.size_line, &img.endian);
	
	color = mlx_get_color_value (env->mlx_ptr, 0x00FFA500);
	img.bpp /= 8;
	ft_put_pixel(&img, color);
	mlx_put_image_to_window (env->mlx_ptr, env->win_ptr, img.img_ptr, 0, 0);

	//ne pas oublier de free, destroy image
}
