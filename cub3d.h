/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:15:08 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/15 13:06:05 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <string.h>
#include <errno.h>

typedef	struct s_map
{
	int nb_line;
	char **tab_map;
}				t_map;

typedef	struct s_env
{
	void *mlx_ptr;
	void *win_ptr;
	int		width;
	int		height;
}				t_env;

typedef struct s_img
{
	void	*img_ptr;
	int		*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;


void	ft_parser(t_map *map, char *file);
int		check_map(t_map *map);
void	init_env(t_env *env);
void	ft_new_image(t_env *env);


#endif
