/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:15:08 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/16 19:09:47 by hbrulin          ###   ########.fr       */
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
# include <string.h>

# define SCREEN_PATH		"screen.bmp"
# define FILE_HEADER_SIZE	14
# define IMG_HEADER_SIZE	40
# define BYTES_PER_PIX		3
# define COMPRESSION		24
# define MAX_WIDTH			2560
# define MAX_HEIGHT 		1440
# define PINK				9961608
# define RIGHTS				0644


typedef struct				s_rgb
{
	unsigned char			b;
	unsigned char			g;
	unsigned char			r;
	unsigned char			a;
}							t_rgb;

typedef union				u_color
{
	unsigned int			all;
	char					tab[4];
	t_rgb					rgb;
}							t_color;

typedef	enum				e_error
{
	SUCCESS,
	INVALID_ARG,
	WRONG_MAP,
	WRONG_INPUT,
	MALLOC_FAIL,
	IMG_FAIL,
	OPEN_ERR,
	MLX_FAIL,
	WRITE_FAIL,
	WRONG_TEX
}							t_error;

typedef struct				s_pos
{
	double					x;
	double					y;
}							t_pos;

typedef struct				s_pos_i
{
	int						x;
	int						y;
}							t_pos_i;

typedef	struct				s_map
{
	char					**tab_map;
	t_list					*list;
	int						nb_line;
	int						nb_char;
	char					player;
}							t_map;

typedef struct				s_img
{
	void					*img_ptr;
	int						*img_data;
	int						bpp;
	int						size_line;
	int						endian;
	int						width;
	int						height;
}							t_img;

typedef struct				s_data
{
	char					*R;
	char					*NO;
	char					*n;
	char					*SO;
	char					*s;
	char					*WE;
	char					*w;
	char					*EA;
	char					*e;
	char					*SP;
	char					*sp;
	char					*F;
	char					*C;
}							t_data;

typedef	struct				s_tex
{
	void					*tex_ptr;
	int						*tex_data;
	int						bpp;
	int						size_line;
	int						endian;
	int						width;
	int						height;
}							t_tex;

typedef struct				s_sprite
{
	double					pos_x;
	double					pos_y;
}							t_sprite;

typedef struct				s_spdata
{
	double					sp_dist;
	double					spcamx;
	double					spcamy;
	double					transx;
	double					transy;
	int						spriteScreenX;
	int						spriteHeight;
	int						drawStartY;
	int						drawEndY;
	int						spriteWidth;
	int						drawStartX;
	int						drawEndX;
}							t_spdata;

typedef struct				s_move
{
	int						up;
	int						down;
	int						left;
	int						right;
	int						strafl;
	int						strafr;
}							t_move;


typedef	struct				s_env
{
	void					*mlx_ptr;
	void					*win_ptr;
	int						width;
	int						height;
	int						flag_save;
	int						nb_sprite;
	t_map					map;
	t_img					*img;
	t_pos					pos;
	t_pos					dir;
	t_pos					plane;
	t_pos					step;
	t_pos					rpos;
	t_pos					rdir;
	t_pos					rdisd;
	t_pos					rdist;
	t_pos_i					rmap;
	t_pos_i					tex;
	t_data					data;
	t_move					move;
	t_color					color_floor;
	t_color					color_ceiling;
	t_spdata				sp;
	t_sprite				*tab_sprite;
	t_tex					*tex1;
	t_tex					*tex2;
	t_tex					*tex3;
	t_tex					*tex4;
	t_tex					*sprite;
	double					speed;
	int						wall;
	unsigned int			color;
	int						wstart;
	int						wend; 
	double					camera;
	int						hit;
	double					rh;
	double					step_tex;
	double					tex_pos;
	double					dist;
	double					*zbuffer;
	int						*sp_order;
	double					*sp_distance;
}							t_env;


int				get_map(t_env *env, char *file);
int				ft_parser(t_env *env);
int				init_env(t_env *env);
int				get_color(t_color *color, char *s);
t_img			*ft_new_image(t_env *env, int width, int height);
void			fill(t_env *env, unsigned int color_floor, unsigned int color_ceiling);
void			ft_put_pixel(t_img *img, unsigned int color, int p_x, int p_y);
int				events(t_env *env);
void			ft_calc_dir(t_env *env);
void			ft_move(t_env *env);
void			ft_ray(t_env *env, int x_img);
void			ft_launch(t_env *env);
int				ft_disp_screen(t_env *env);
void			ft_init_ray(t_env *env, int x);
void			ft_direction_ray(t_env *env);
void			ft_hit_ray(t_env *env);
void			ft_size_ray(t_env *env);
t_tex			*ft_new_tex(t_env *env, char *file);
void			pix_color(t_env *env);
void			add_sprite(t_env *env);
void			ft_sprite_calc(t_env *env, int i);
int				ft_save(t_env *env);
int				deal_exit(t_env *env);
char			*ft_strdup_no_space(const char *s);
void			init_sprite(t_env *env);
void			add_sprite(t_env *env);
void			ft_sprite_calc(t_env *env, int i);
size_t			tab_size(char **tab);
int				ft_error(int error, t_env *env);
char			*ft_realloc(char *src);
int				init_var(t_env *env, char *s);
int				launch_save(t_env *env);
int				init_flag_save(t_env *env, int argc, char *s);

#endif
