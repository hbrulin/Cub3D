/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 15:58:55 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/18 17:13:44 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "keycode.h"
#include <stdio.h>

// plus le rayon va loin, plus la distance qui separe la camera de l'obstacle est importante
// plus l'obstacle est loin, plus l'objet paraitra petit
//Les murs ont toujours un angle de 90° avec le sol
//Les murs sont des cubes qui ont tous la même taille
//Le sol est toujours plat

//Parametres a definir :
// hauteur camera, 
// orientation camera (angle)
// champ visuel camera
// position camera -pos
// taille ecran projection

void	ft_ray(t_env *env)
{
	float plane_x = 0;
	float plane_y = 0.66;



}


