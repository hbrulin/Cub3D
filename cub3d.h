/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:15:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/08 17:02:06 by hbrulin          ###   ########.fr       */
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

//changer par textures
# define COLOR_NORTH 0x116CC7
# define COLOR_SOUTH 0xDD985C
# define COLOR_EAST 0xA91101
# define COLOR_WEST 0xEFD242

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
	double x;
	double y;
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

typedef	struct s_tex
{
	void	*tex_ptr;
	int	*tex_data;
	int	bpp;
	int	size_line;
	int	endian;
	int	width;
	int	height;
}				t_tex;

typedef struct	s_sprite
{
	double sp_dist;
	double pos_x;
	double pos_y;
	double spcamx;
	double spcamy;
	double transx;
	double transy;
	int spriteScreenX;
	int spriteHeight;
	int	drawStartY;
	int drawEndY;
	int spriteWidth;
	int drawStartX;
	int drawEndX;
}				t_sprite;

typedef	struct s_env
{
	void *mlx_ptr;
	void *win_ptr;
	int		width;
	int		height;
	t_map	map;
	t_img	*img;
	t_pos 	pos;
	t_pos	dir;
	t_pos	plane;
	t_pos	step;
	t_pos	rpos;
	t_pos	rdir;
	t_pos	rdisd;
	t_pos	rdist;
	t_data	data;
	t_sprite	sp;
	double	speed;
	int up;
	int down;
	int left;
	int right;
	int wall;
	unsigned int color;
	int wstart;
	int wend; 
	double camera;
	int hit;
	double rh;
	int rmap_x;
	int rmap_y;
	t_tex *tex1;
	t_tex *tex2;
	t_tex *tex3;
	t_tex *tex4;
	t_tex *sprite;
	int tex_x;
	int tex_y;
	double step_tex;
	double tex_pos;

}				t_env;

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



int				get_map(t_env *env, char *file);
int				ft_parser(t_env *env);
int				init_env(t_env *env);
int	get_color(t_env *env, t_color *color_floor, t_color *color_ceiling);
t_img	*ft_new_image(t_env *env, int width, int height);
int		fill_floor_ceiling(t_env *env);
void	fill(t_env *env, unsigned int color_floor, unsigned int color_ceiling);
void	ft_put_pixel(t_img *img, unsigned int color, int p_x, int p_y);
void	events(t_env *env);
void	ft_calc_dir(t_env *env);
void	ft_move(t_env *env);
void	ft_ray(t_env *env, int x_img);
void	ft_launch(t_env *env);
void		ft_disp_screen(t_env *env);
void	ft_init_ray(t_env *env, int x);
void	ft_direction_ray(t_env *env);
void	ft_hit_ray(t_env *env);
void	ft_size_ray(t_env *env);
t_tex	*ft_new_tex(t_env *env, char *file);
void	pix_color(t_env *env);
void	add_sprite(t_env *env);
void	ft_sprite_calc(t_env *env);

#endif
