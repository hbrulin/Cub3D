/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:05:41 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 14:06:41 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

unsigned int	rgb_to_hex(int r, int g, int b)
{
	unsigned int hex = (0 << 24) | ((unsigned char)r << 16) | ((unsigned char)g << 8) | ((unsigned char)b<<0); 
	printf("%u", hex);
	return(hex);
}
