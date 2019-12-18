/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:58:55 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/18 19:19:45 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>


void	ft_ray(t_env *env)
{
	int planeX = 0;
	int planeY = 1; 

	int x_img = 0; //position de depart du trace sur img
	int y_img = 0; //position de depart du trace sur img
	float ray_pos_x = env->pos.x; //position de depart du rayon sur x
	float ray_pos_y = env->pos.y; //position de depart du rayon sur y
	int cameraX;
	float ray_dir_x;
	float ray_dir_y;

/*Le centre de l’écran de projection sur X est égal à 0
La partie gauche de l’écran est égale à -1
La partie droite de l’écran est égale à 1*/

	while (x_img <= env->img->width)
	{
		cameraX = (2 * x_img / env->img->width) - 1; //position de la colonne p/r au centre de l'ecran
		ray_dir_x = env->dir.x + planeX * cameraX; // direction du rayon sur X
		ray_dir_y = env->dir.y + planeY * cameraX; // direction du rayon sur Y
	}

	//sur quelle case est la camera
	int mapX = (int)ray_pos_x; //On conv un nombre décimal en valeur entière.
	int mapY = (int)ray_pos_y;

	//distance que le rayon parcourt entre sa position de départ et le mur.
	float side_dist_x;
	float side_dist_y;

	//les distances que le rayon doit parcourir sur chaque axe pour aller au prochain point d’intersection.
	float deltaDistX = sqrt(1+(ray_dir_y * ray_dir_y)/(ray_dir_x * ray_dir_x));
	float deltaDistY = sqrt(1+(ray_dir_x * ray_dir_x)/(ray_dir_y * ray_dir_y));

	// direction du rayon : negative (-1) ou positive (1), sur chaque axe.
	int stepX;
	int stepY;

	//si contact mur
	int hit = 0;
	// 0, 1, 2, 3 ->permet de connaitre otirntation du mur touche -> utile pour texture
	int hit_side;

	//Si la direction du rayon sur X est inférieure à zéro, alors le vecteur de direction du rayon sur cet axe est négatif.
	//Autrement dit le prochain pas du rayon dans la map se fera vers la gauche.


	//calcule le vecteur de direction et la longueur entre deux segments
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
			hit_side = 0; //orientation du mur - ici soit nord soit sud, il faut diviser selon qu'on descend ou monte pour avoir lequel
		}
		else
		{
			side_dist_y += deltaDistY;
			mapY += stepY;
			hit_side = 1;
		}
		if(env->map.tab_map[mapY][mapX] == 1)
			hit = 1;
	}

	int wall_dist; //distane corrigee du +1 ajoute plus haut

	//si mur touché sur axe x
	if (hit_side == 0)
		wall_dist = abs((mapX - ray_pos_x + (1 - stepX) / 2) / ray_dir_x);
	else
		wall_dist = abs((mapY - ray_pos_y + (1 - stepY) / 2) / ray_dir_y);
	
	//calcul hauteur colonne a tracer
	int hauteur = abs(env->img->height / wall_dist);

	int draw_start = - (hauteur / 2 + env->img->height / 2);
	int draw_end = (hauteur / 2 + env->img->height / 2);

	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= env->img->height)
		draw_end = env->img->height - 1;


	//tracer
	int d = draw_start;
	while (d < draw_end)
	{
		if (hit_side == 1)
			ft_put_pixel(env->img, 0x00A0ACAA, x_img, d);
		d++;
	}
}


/* 	int FOV = 60;
	int wall_height = 64; //quelle est l'unite ici? 
	int player_height = wall_height / 2;
	int planeX = 320; //faut-il que ce soit la resolution del'ecran?
	int planeY = 200;
	int plane[planeY][planeX];
	float dist_to_plane = 160 / tan(env->pos.angle_d); //from layer to projection plane
	float angle_ray = FOV / planeX;     //angle btw rays - wall = 320 colonnes

	//The ray on the extreme left of the FOV will be projected onto column 0 of the projection plane, 
	//and the right most ray will be projected onto column 319 of the projection plane.

	//int new_angle = env->pos.angle_d - FOV / 2;

	int i = 0;
	while (plane[i]) //pour chqaue colonne
	{
		//trace ray until hits wall
		//record distance si mur atteint : pythagore
		dist_to_column += angle_ray; // - FOV / 2
		i++;
	}

	int projected_column_height = (wall_height/dist_to_column) * dist_to_plane;
*/
