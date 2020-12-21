/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mflorido <mflorido@student.42madrid.co>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 15:19:30 by mflorido          #+#    #+#             */
/*   Updated: 2020/11/06 13:44:23 by tsierra-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "libft/libft.h"

typedef struct	s_img
{
	//Puntero hacia la imágen sobre la que vamos a pintar
	void		*img_ptr;
	//El buffer de la imágen en la que vamos a pintar
	char		*img_buff;
	//El número de bits por pixel de la imágen
	int			bpp;
	//El tamaño de una línea
	int			line_size;
	//1 si es 0xBBGGRRAA y 0 si es 0xAARRGGBB
	int			endian;
}				t_img;

void		put_pixel_to_img(t_img *img, unsigned color, int x, int y)
{
	int	pixel;

	//El buffer es un string con toda la info, cada img->line_size carácteres tenemos
	//Una línea (Y) y cada 4 carácteres (RGBA) tenemos una nueva X
	//Digo carácter porque funciona como string, pero son bytes realmente
	pixel = ((int)y * img->line_size) + (x * 4);
	if (img->endian == 1)
	{
		//El primer byte de los cuatro del pixel va a ser el canal Alpha
		//Por eso cogemos color y le quitamos 24 bits a la derecha
		//0xAARRGGBB => 0xAA______ una vez más los _ se reemplazan por 0
		//0xAA000000 => 0xAA
		img->img_buff[pixel + 0] = (color >> 24);
		//El segundo byte de los cuatro del pixel va a ser el canal Red
		//Por eso cogemos color y le quitamos 16 bits a la derecha
		//0xAARRGGBB => 0xAARR____ una vez más los _ se reemplazan por 0
		//0xAARR0000 => 0xAARR y hacemos un and binario, por lo que:
		//0xAARR & 0x00RR se convierte en 0x00RR => 0xRR
		img->img_buff[pixel + 1] = (color >> 16) & 0xFF;
		//El tercer byte de los cuatro del pixel va a ser el canal Green
		//Por eso cogemos color y le quitamos 8 bits a la derecha
		//0xAARRGGBB => 0xAARRGG__ una vez más los _ se reemplazan por 0
		//0xAARR0000 => 0xAARRGG y hacemos un and binario, por lo que:
		//0xAARRGG & 0x0000GG se convierte en 0x0000GG => 0xGG
		img->img_buff[pixel + 2] = (color >> 8) & 0xFF;
		//El tercer byte de los cuatro del pixel va a ser el canal Blue
		//Por eso cogemos color y le quitamos 0 bits a la derecha
		//0xAARRGGBB => 0xAARRGGBB y hacemos un and binario, por lo que:
		//0xAARRGGBB & 0x000000BB se convierte en 0x000000BB => 0xBB
		img->img_buff[pixel + 3] = (color) & 0xFF;
		//El and binario & es para tener solamente números de 00 a ff (0 - 255)
	}
	else if (img->endian == 0)
	{
		img->img_buff[pixel + 0] = (color) & 0xFF;
		img->img_buff[pixel + 1] = (color >> 8) & 0xFF;
		img->img_buff[pixel + 2] = (color >> 16) & 0xFF;
		img->img_buff[pixel + 3] = (color >> 24);
		//En este caso sería exactamente igual, pero inversamente, el byte 0 será
		//para el canal B, el 1 para el G, el 2 para R y por último el 3 para A
	}
}

unsigned	rgba_to_hex(unsigned r, unsigned g, unsigned b, unsigned a)
{
	unsigned	color;

	//Alpha
	//El color va a ser igual a alpha (0 - 255) o lo que es lo mismo; de 00 a ff
	color = a & 0xFF;
	//Muevo 8 bits hacia la izquierda (1 byte) de 0xAA a 0xAA__ Como el __ no sabe que es, rellena con 0 => 0xAA00
	color <<= 8;
	//Red
	//Al color le meto el valor de R con OR binario 0xAA00 | 0x00RR por lo que se quedaría siempre así: 0xAARR
	color |= r & 0xFF;
	//Muevo 8 bits hacia la izquierda (1 byte) de 0xAARR a 0xAARR__ Como el __ no sabe que es, rellena con 0 => 0xAARR00
	color <<= 8;
	//Green
	//Al color le meto el valor de G con OR binario 0xAARR00 | 0x0000RR por lo que se quedaría siempre así: 0xAARRGG
	color |= g & 0xFF;
	//Muevo 8 bits hacia la izquierda (1 byte) de 0xAARR a 0xAARRGG__ Como el __ no sabe que es, rellena con 0 => 0xAARRGG00
	color <<= 8;
	//Blue
	//Al color le meto el valor de B con OR binario 0xAARR00 | 0x000000BB por lo que se quedaría siempre así: 0xAARRGGBB
	color |= b & 0xFF;
	//Finalmente obtendremos un hexadecimal 0xAARRGGBB
	//Es muy importante que tengamos primero Alpha y luego RGB ya que esta es la configuración de endian 1.
	//En caso de tener endian 0 sería al revés 0xBBGGRRAA pero eso lo tendremos en cuenta solo a la hora de pintar, para
	//Estandarizar el código
	return (color);
}

int			main(void)
{
	//Puntero hacia la minilibx
	void	*mlx_ptr;
	//Puntero hacia una ventana gráfica
	void	*wdw_ptr;
	//La estructura con mi imágen
	t_img	img;
	//Coordenadas para pintar la imágen
	int		x;
	int		y;
	int		red;
	int		green;
	int		blue;
	int		range;

	//Inicializamos mlx
	mlx_ptr = mlx_init();
	//Creamos una ventana gráfica
	wdw_ptr = mlx_new_window(mlx_ptr, 1920, 600, "MiniLibX");
	//Creamos una imágen de 300x300 en negro
	img.img_ptr = mlx_new_image(mlx_ptr, 1920, 600);
	//Obtenemos su información
	img.img_buff = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.line_size, &img.endian);
	//Escribimos en toda la imágen
	/*
	x = 0;
	while (x < 300) //< 300 porque la imágen tiene 300 de ancho
	{
		y = 0;
		while (y < 300)
		{
			put_pixel_to_img(&img, rgba_to_hex(255, 0, 0, 0), x, y);
			y++;
		}
		x++;
	}*/

	//Código para cosas raras:
	red = 255;
	green = 0;
	blue = 0;
	x = 0;
	range = 125;
	while (x < 1920) //< 300 porque la imágen tiene 300 de ancho
	{
		y = 0;
		while (y < 600)
		{
			if (red == 255 && green == 0)
				blue += range;
			if (blue == 255 && green == 0)
				red -= range;
			if (red == 0 && blue == 255)
				green += range; 
			if (green == 255 && red == 0)
				blue -= range;
			if (blue == 0 && green == 255)
				red += range;
			if (red == 255 && blue == 0)
				green -= range;
			put_pixel_to_img(&img, rgba_to_hex(red, green, blue, 0), x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(mlx_ptr, wdw_ptr, img.img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}
