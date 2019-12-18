/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:15:08 by hbrulin           #+#    #+#             */
/*   Updated: 2019/12/18 11:22:36 by hbrulin          ###   ########.fr       */
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

typedef struct s_pos
{
	float x;
	float y;
	int angle_d;
	float angle_rad;
	int flag_angle_right;
}				t_pos;

typedef	struct s_map
{
	char **tab_map;
	t_list	*list;
	int	nb_line;
	char	player;
}				t_map;

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

typedef	struct s_env
{
	void *mlx_ptr;
	void *win_ptr;
	int		width;
	int		height;
	t_map	map;
	t_img	*img;
	t_pos 	pos;
}				t_env;

typedef struct s_data
{
	char *R;
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char *S;
	char *F;
	char *C;
}			t_data;

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



int				get_map(t_env *env, t_data *data, char *file);
int				ft_parser(t_env *env);
int				init_env(t_env *env, t_data *data);
int	get_color(t_data *data, t_color *color_floor, t_color *color_ceiling);
t_img	*ft_new_image(t_env *env, int width, int height);
int		fill_floor_ceiling(t_env *env, t_data *data);
void	fill(t_env *env, unsigned int color_floor, unsigned int color_ceiling);
void	ft_put_pixel(t_img *img, unsigned int color, int p_x, int p_y);
void	events(t_env *env);
void	ft_y_down(t_env *env);
void	ft_y_up(t_env *env);
void	ft_x_down(t_env *env);
void	ft_x_up(t_env *env);
void	ft_angle_move_W(t_env *env);

#endif
