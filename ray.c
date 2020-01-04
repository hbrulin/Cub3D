/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:58:55 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/19 18:29:58 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"

void	ft_launch(t_env *env)
{
	int x_img = 0; //position de depart du trace sur img
	//int y_img = 0; //position de depart du trace sur img

	while (x_img <= env->img->width)
	{
		ft_ray(env, x_img);
		x_img++;
	}
	mlx_put_image_to_window (env->mlx_ptr, env->win_ptr, env->img->img_ptr, 0, 0);
}

void	ft_ray(t_env *env, int x_img)
{

	//int x_img = 0; //position de depart du trace sur img
	int y_img = 0; //position de depart du trace sur img
	double ray_pos_x = env->pos.x; //position de depart du rayon sur x
	double ray_pos_y = env->pos.y; //position de depart du rayon sur y
	int cameraX;
	double ray_dir_x;
	double ray_dir_y;

/*Le centre de l’écran de projection sur X est égal à 0
La partie gauche de l’écran est égale à -1
La partie droite de l’écran est égale à 1*/

	cameraX = (2 * x_img / env->img->width) - 1; //position de la colonne p/r au centre de l'ecran
	ray_dir_x = env->dir.x + env->plane.x * cameraX; // direction du rayon sur X
	ray_dir_y = env->dir.y + env->plane.y * cameraX; // direction du rayon sur Y

	//sur quelle case est la camera
	int mapX = (int)ray_pos_x; //On conv un nombre décimal en valeur entière.
	int mapY = (int)ray_pos_y;

	//distance que le rayon parcourt entre sa position de départ et le mur.
	double side_dist_x;
	double side_dist_y;

	//les distances que le rayon doit parcourir sur chaque axe pour aller au prochain point d’intersection.
	double deltaDistX = sqrt(1+(ray_dir_y * ray_dir_y)/(ray_dir_x * ray_dir_x));
	double deltaDistY = sqrt(1+(ray_dir_x * ray_dir_x)/(ray_dir_y * ray_dir_y));

	// direction du rayon : negative (-1) ou positive (1), sur chaque axe.
	int stepX;
	int stepY;

	//si contact mur
	int hit = 0;
	// 0, 1, 2, 3 ->permet de connaitre otirntation du mur touche -> utile pour texture
	int hit_side;

	//Si la direction du rayon sur X est inférieure à zéro, alors le vecteur de direction du rayon sur cet axe est négatif.
	//Autrement dit le prochain pas du rayon dans la map se fera vers la gauche.


	//calcule le vecteur de direction et la longueur du rayon
	if (ray_dir_x < 0)
	{
		stepX = - 1; //vecteur de direction
		side_dist_x = (ray_pos_x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		side_dist_x = (mapX + 1.0 - ray_pos_x) * deltaDistX; //car on touche mur d'un cote et il faut avancer
	}
	if (ray_dir_y < 0)
	{
		stepY = -1;
		side_dist_y = (ray_pos_y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		side_dist_y = (mapY + 1.0 - ray_pos_y) * deltaDistY; //car on touche mur d'un cote et il faut avancer
	}
	
	while (hit == 0)
	{
		//passe a la case suivante sur x ou y 
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += deltaDistX; //aggrandis le rayon
			mapX += stepX; //on change de case sur X
			hit_side = 0; //orientation du mur - ici soit nord soit sud, il faut separer selon qu'on descend ou monte pour avoir lequel
		}
		else
		{
			side_dist_y += deltaDistY;
			mapY += stepY;
			hit_side = 1;
		}
		if(env->map.tab_map[mapY][mapX] == '1') 
			hit = 1;
	}

	double wall_dist; //distane corrigee du +1 ajoute plus haut

	//si mur touché sur axe x
	if (hit_side == 0)
		wall_dist = fabs((mapX - ray_pos_x + (1 - stepX) / 2) / ray_dir_x);
	else
		wall_dist = fabs((mapY - ray_pos_y + (1 - stepY) / 2) / ray_dir_y);
	
	//calcul hauteur colonne a tracer
	int hauteur = fabs(env->img->height / wall_dist);
	//ft_putnbr_fd(hauteur, 1);
	//ft_putchar_fd('\n', 1);

	int draw_start = (-1 * hauteur / 2 + env->img->height / 2);
	int draw_end = (hauteur / 2 + env->img->height / 2);

	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= env->img->height)
		draw_end = env->img->height - 1;
	//ft_putnbr_fd(draw_start, 1);
	//ft_putchar_fd('\n', 1);
	//ft_putnbr_fd(draw_end, 1);
	//ft_putchar_fd('\n', 1);

	unsigned int color = mlx_get_color_value (env->mlx_ptr, 0xB62929);
	unsigned int color2 = mlx_get_color_value (env->mlx_ptr, 0x7F7474);

	//tracer
	y_img = draw_start;
	//ft_putnbr_fd(y_img, 1);
	//ft_putchar_fd('\n', 1);
	while (y_img < draw_end)
	{
		if (hit_side == 1)
			ft_put_pixel(env->img, color, x_img, y_img);
		else
			ft_put_pixel(env->img, color2, x_img, y_img);
		y_img++;
	}
}
