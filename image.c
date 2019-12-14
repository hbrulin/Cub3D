/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:03:01 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/14 21:47:36 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_put_pixel(t_img *img, unsigned int color)
{
	int p_x;
	int p_y;

	// il faut verifier que le pixel n'est pas en dehors de la map
	p_x = 1;
	p_y = 2;

	while (p_x < 500 && p_y < 500)
	{
		*(img->img_data + p_x * (img->size_line * p_y)) = color;
		p_x++;
		p_y++;
	}
}

void	ft_new_image(t_env *env)
{
	t_img img; //y a til une seule image pour tout le programme, comment ca marche
	unsigned int color;
	
	img.img_ptr = mlx_new_image (env->mlx_ptr, env->width, env->height );

    img.img_data = mlx_get_data_addr (img.img_ptr, &img.bpp, &img.size_line, &img.endian);
	
	color = mlx_get_color_value (env->mlx_ptr, 255);
	ft_put_pixel(&img, color);

	mlx_put_image_to_window (env->mlx_ptr, env->win_ptr, img.img_ptr, 0, 0);

	//ne pas oublier de free, destroy image
}
