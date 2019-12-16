/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 21:03:01 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 16:09:50 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	ft_put_pixel(t_img *img, unsigned int color, int p_x, int p_y)
{
	//verifier avant que le pixel n'est pas en dehors de l'img 
	img->img_data[p_y * img->height + p_x] = color;
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
