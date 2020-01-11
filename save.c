/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:11:05 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/11 14:58:30 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//sauver la première image rendue au format bmp lorsque le second argument est "–save".

#include "cub3d.h"
#include "keycode.h"

int	write_colors(t_env *env, int fd, int height, int width)
{
	/*int x = 0;
	int y = height - 1; 
	unsigned int byte;
	while(y >= 0)
	{
		while(x < width)
		{
			byte = env->img->img_data[y * env->img->width + x];
			write(fd, ft_itoa(byte), 1);
			x++;
		}
		y--;
	}*/

	unsigned char	abc[3] = {0, 0, 0};
	int					i;
	int					j;


	i = 0;
	while (i < (int)env->height)
	{
		j = 0;
		while (j < (int)env->width)
		{
			abc[0] = (240 & (env->img->img_data[(height - i) *
			width + j]) >> 16);
			abc[1] = (240 & (env->img->img_data[(height - i) *
			width + j]) >> 8);
			abc[2] = (240 & env->img->img_data[(height - i) *
			width + j]);
			write(fd, abc + 2, 1);
			write(fd, abc + 1, 1);
			write(fd, abc, 1);
			j++;
		}
		i++;
	}
	return (1);

}

static void set_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

unsigned char *create_file_header(t_env *env, int pad)
{
	int file_size;
	static unsigned char	file_header[14] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//3 BYTES PER PIXEL car compression 24
	file_size = 54 + (3 * ((int)env->width + pad) * (int)env->height);

	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M'); //A
	set_in_char(file_header + 2, file_size);
	set_in_char(file_header + 10, 54);
	return(file_header);
}

unsigned char *create_img_header(int height, int width)
{
	static unsigned char img_header[40] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	set_in_char(img_header, 40);
	set_in_char(img_header + 4, width);
	set_in_char(img_header + 8, height);
	img_header[12] = (unsigned char)(1);
	set_in_char(img_header + 14, 24); // l'image est codée en 24 bits, chaque pixel est codé par un entier 24 bits (RVB), ordre little-endian, c'est-à-dire que les trois octets codent successivement les niveaux de bleu, vert et rouge.
	return(img_header);
}

void	ft_save(t_env *env)
{
	int height;
	int width;
	unsigned char *file_header;
	unsigned char *img_header;
	int fd;
	height = env->height - 1; // -1 ???
	width = env->width;
	int pad = (4 - ((int)env->width * 3) % 4) % 4; // car il faut nb de byte multiple de 4

	file_header = create_file_header(env, pad);
	img_header = create_img_header(height, width);
	fd = open(SCREEN_PATH, O_RDWR | O_CREAT | O_APPEND); //securiser + ATTENTION JE N'AI PAS LES DROITS SUR LE FICHIER BMP
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, img_header, IMG_HEADER_SIZE);
	write_colors(env, fd, height, width);
	close(fd);
}
