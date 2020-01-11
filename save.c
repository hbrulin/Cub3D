/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 14:11:05 by hbrulin           #+#    #+#             */
/*   Updated: 2020/01/11 14:13:41 by hbrulin          ###   ########.fr       */
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

static void set_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

unsigned char *create_file_header(t_env *env)
{
	int pad;
	int file_size;
	static unsigned char	file_header[] = {
		0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	pad = (4 - ((int)env->width * 3) % 4) % 4;
	file_size = 54 + (3 * ((int)env->width + pad) * (int)env->height);

	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M'); //A
	set_in_char(file_header + 2, file_size);
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
	set_in_char(img_header + 4, width);
	set_in_char(img_header + 8, height);
	img_header[12] = (unsigned char)(1);
	img_header[14] = (unsigned char)(24); //est ce la bonne valeur?
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
	fd = open(SCREEN_PATH, O_WRONLY | O_CREAT | O_APPEND | O_RDONLY);
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, img_header, IMG_HEADER_SIZE);
	write_colors(env, height, width, fd);
	close(fd);
}
