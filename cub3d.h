/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:15:08 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 14:08:06 by hbrulin          ###   ########.fr       */
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

typedef	enum	e_error
{
	SUCCESS,
	NO_MAP,
	WRONG_MAP,
	WRONG_INPUT,
	MALLOC_FAIL
}				t_error;

typedef	struct s_map
{
	char **tab_map;
	t_list	*list;
	int	nb_line;
	char *R;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *S;
	char *F;
	char *C;
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
	int		width;
	int		height;
}				t_img;

int		ft_parser(t_map *map);
int		get_map(t_map *map, char *file);
int		check_map(t_map *map);
int		init_env(t_env *env, t_map *map);
void	ft_new_image(t_env *env);
unsigned int	rgb_to_hex(int r, int g, int b);


#endif
