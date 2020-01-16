/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:41:59 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 15:42:17 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_error(int error, t_env *env)
{
	if (error == INVALID_ARG)
		ft_putstr("Error\n Invalid argument");
	if (error == WRONG_INPUT)
		ft_putstr("Error\n Invalid input");
	if (error == WRONG_MAP)
		ft_putstr("Error\n Invalid map");
	if (error == WRONG_MAP)
		ft_putstr("Error\n Invalid input");
	if (error == MALLOC_FAIL)
		ft_putstr("Error\n Memory allocation has failed");
	if (error == OPEN_ERR)
		ft_putstr("Error\n File could not be opened");
	if (error == IMG_FAIL)
		ft_putstr("Error\n Image could not be allocated");
	if (error == MLX_FAIL)
		ft_putstr("Error\n Mlx failure");
	if (error == MLX_FAIL)
		ft_putstr("Error\n Writing in bmp has failed");
	if (error == WRONG_TEX)
		ft_putstr("Error\n Wrong path for texture");
	deal_exit(env);
	return (error);
}
