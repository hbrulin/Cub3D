/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:15:08 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/16 19:44:36 by hbrulin          ###   ########.fr       */
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

typedef	enum	e_error
{
	SUCCESS,
	NO_MAP,
	WRONG_MAP,
	WRONG_INPUT,
	MALLOC_FAIL,
	IMG_FAIL
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

/*typedef struct s_color
{
	unsigned char r_floor;
	unsigned char g_floor;
	unsigned char b_floor;
	int r_ceiling;
	int g_ceiling;
	int b_ceiling;
	unsigned int color_floor;
	unsigned int color_ceiling;
}				t_color;*/

typedef struct	s_rgb
{
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
}				t_rgb;

typedef union	u_color
{
		unsigned int	all;
		char			tab[4];
		t_rgb			rgb;
}				t_color;



int				get_map(t_map *map, char *file);
int				ft_parser(t_map *map);
int				init_env(t_env *env, t_map *map);
int	get_rgb(t_map *map, t_color *color_floor, t_color *color_ceiling);
//unsigned int	rgb_to_hex(int r, int g, int b);
t_img	*ft_new_image(t_env *env, int width, int height);
void	fill(t_img *img, unsigned int color);
int		fill_floor_ceiling(t_env *env, t_map *map);
void	ft_put_pixel(t_img *img, unsigned int color, int p_x, int p_y);
void	events(t_env *env);


#endif
