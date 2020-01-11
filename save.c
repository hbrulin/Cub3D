/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:11:05 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/11 13:06:46 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//sauver la première image rendue au format bmp lorsque le second argument est "–save".

#include "cub3d.h"
#include "keycode.h"

void	write_colors(t_env *env, int height, int width, int fd)
{
	int x = 0;
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
	}
}

unsigned char *create_file_header(t_env *env)
{
	static unsigned char	file_header[] = {
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	//que fairte du champ reserve?
	int file_size = FILE_HEADER_SIZE + IMG_HEADER_SIZE + env->img->bpp * (env->width * env->height); //bonne formule?

	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M'); //A
	file_header[2] = (unsigned char)file_size;
	//car sur 4 bits
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	//offset
	file_header[10] = (unsigned char)FILE_HEADER_SIZE + IMG_HEADER_SIZE;
	return(file_header);
}

unsigned char *create_img_header(int height, int width)
{
	static unsigned char img_header[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	img_header[0] = (unsigned char)(IMG_HEADER_SIZE);
	img_header[4] = (unsigned char)(width);
	img_header[5] = (unsigned char)(width >> 8);
	img_header[6] = (unsigned char)(width >> 16);
	img_header[7] = (unsigned char)(width >> 24);
	img_header[8] = (unsigned char)(height);
	img_header[9] = (unsigned char)(height >> 8);
	img_header[10] = (unsigned char)(height >> 16);
	img_header[11] = (unsigned char)(height >> 24);
	img_header[12] = (unsigned char)1;
	img_header[14] = (unsigned char)0; //est ce la bonne valeur?
	return(img_header);
}

void	ft_save(t_env *env)
{
	int height;
	int width;
	unsigned char *file_header;
	unsigned char *img_header;
	int fd;
	height = env->height; // -1 ???
	width = env->width;

	file_header = create_file_header(env);
	img_header = create_img_header(height, width);
	fd = open(SCREEN_PATH, O_WRONLY);
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, img_header, IMG_HEADER_SIZE);
	write_colors(env, height, width, fd);
	close(fd);
}
