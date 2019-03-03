/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsebasti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 15:06:25 by qsebasti          #+#    #+#             */
/*   Updated: 2018/04/25 19:02:51 by qsebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "../minilibx_macos/mlx.h"
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <OpenGL/glext.h>
# include <GLUT/glut.h>
# include "../libft/libft.h"
# include <math.h>
# include <pthread.h>
# include <time.h>

/*
** Colors.
*/

# define SNOW 0xfffafa

# define SUNSET1 0xe7e042
# define SUNSET2 0xe3d019
# define SUNSET3 0xdb9dbf
# define SUNSET4 0x9967d8

# define FRA1 0x999898
# define FRA2 0xd90000
# define FRA3 0xffffff
# define FRA4 0x00165b

# define FLAMES1 0xffe970
# define FLAMES2 0xffcb5c
# define FLAMES3 0xe75f41
# define FLAMES4 0x38160a

# define LIGHT1 0xf1f5f9
# define LIGHT2 0x4296ec
# define LIGHT3 0x2439a4
# define LIGHT4 0x192734

# define RED1 0xdb0000
# define RED2 0xb40000
# define RED3 0x830000
# define RED4 0x4b0000

# define KID1 0xe8ff29
# define KID2 0x2fff00
# define KID3 0x3ccdec
# define KID4 0xfd1bff
# define KID5 0xf00000

# define SUN1 0xfeff7d
# define SUN2 0xcffbff
# define SUN3 0xb6f9ff
# define SUN4 0x79f3fd
# define SUN5 0x00ecff

# define SWAN1 0xffffff
# define SWAN2 0xff8100
# define SWAN3 0x0f0202
# define SWAN4 0xd4cdcd
# define SWAN5 0x452424

# define MUNCH1 0x003333
# define MUNCH2 0x669999
# define MUNCH3 0xcc9966
# define MUNCH4 0xcc6600
# define MUNCH5 0xcc3300

# define BGT1 0xe6ecf0
# define BGT2 0xfed044
# define BGT3 0x1d809f
# define BGT4 0x5a7f95
# define BGT5 0x0c508b

# define PURPLE1 0xa9457d
# define PURPLE2 0x7b3b8a
# define PURPLE3 0x61378b
# define PURPLE4 0x342b80
# define PURPLE5 0x222479

# define AEC1 0xff0000
# define AEC2 0xff8000
# define AEC3 0xffff00
# define AEC4 0x00ff00
# define AEC5 0x00ffff
# define AEC6 0x0000ff
# define AEC7 0xff00ff

/*
**	Masks et events pour la gestion du clavier et de la souris par la mlx.
*/

# define KPRESSMASK 1L << 0
# define KRELEASEMASK 1L << 1
# define BPRESSMASK 1L << 2
# define BRELEASEMASK 1L << 3
# define POINTERMOTIONMASK 1L << 6
# define SNOTIFYMASK 1L << 17
# define KPRESS 2
# define KRELEASE 3
# define BPRESS 4
# define BRELEASE 5
# define MOTION 6
# define DESTROY 17

/*
**	Keycode utilises.
*/

# define KEY_ESC 53
# define KEY_ENTER 36
# define KEY_BCKSPC 51
# define KEY_SPC 49
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_0 82
# define KEY_1 83
# define KEY_2 84
# define KEY_3 85
# define KEY_4 86
# define KEY_5 87
# define KEY_6 88
# define KEY_7 89
# define KEY_8 91
# define KEY_9 92
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_MULT 67
# define KEY_DIV 75
# define KEY_A 0
# define KEY_H 4
# define KEY_C 8
# define KEY_F 3
# define KEY_P 35
# define KEY_M 46
# define LSHIFT 257
# define RSHIFT 258
# define LCTRL 256
# define RCTRL 269
# define RCLICK 2
# define LCLICK 1
# define FWDSCROLL 4
# define BWDSCROLL 5

/*
**	Taille de la fenetre, fractals et nombre de threads.
*/

# define WIDTH 800
# define HEIGHT 800
# define MANDELBROT 0
# define JULIA 1
# define BURNING 2
# define TRICORN 3
# define CELTIC 4
# define WRONG 5
# define THREADS 8
# define USAGE "usage: ./fractol mandelbrot | julia | burningship | tricorn |"
# define ROT M_PI / 32

/*
**	Defines utilises pour le tableau de double pour plus de clarte sur le
**	multithread.
*/

# define X 0
# define Y 1
# define XMIN 2
# define YMIN 3
# define TMP 4
# define ZR 5
# define ZI 6
# define CR 7
# define CI 8
# define I 9
# define STEPX 10
# define XMAX 11

/*
**	Union pour modifier les composantes ARGB de chaque pixel.
*/

typedef union		u_col
{
	int				color;
	unsigned char	argb[4];
}					t_col;

/*
** Structure pour les palettes de couleurs avec le nombre de palettes et la
** longueur de la palette.
*/

typedef struct		s_pal
{
	int				len;
	int				tab[10];
}					t_pal;

typedef struct		s_env
{
	void			*win;
	void			*mlx;
	void			*img;
	char			*str;
	char			*data;
	int				bpp;
	int				s_len;
	int				end;
	int				key[300];

	int				it_max;
	double			w;
	double			h;
	int				i;
	int				nb;
	char			*tab[7];
	int				mouse[10];
	int				palette;
	time_t			temps;
	int				power;
	int				*colors;

	int				mouse_x;
	int				mouse_y;

	int				x;
	int				y;

	double			x1;
	double			x2;
	double			y1;
	double			y2;
	double			tmp;

	double			tmpx;
	double			tmpy;
	double			stepx;
	double			stepy;

	double			z_r;
	double			z_i;
	double			c_r;
	double			c_i;

	double			tx;
	double			ty;
}					t_env;

/*
**	Structure pointant sur l'env pour le multithread.
*/

typedef struct		s_th
{
	int				nb;
	t_env			*env;
}					t_th;

/*
**	Fonctions annexes.
*/

int					fractol_error(int a);
void				ft_setenv(t_env *e);
void				ft_set_frac(int i, t_env *e);
void				ft_choose_frac(int i, t_env *e);
void				print_string_mlx(t_env *e);

/*
**	Fonctions utilisees par la mlx.
*/

int					keypress(int keycode, t_env *e);
int					keyrelease(int keycode, t_env *e);
int					keyhook(t_env *e);
int					mousehook(t_env *e);
int					mousemovehook(int x, int y, t_env *e);
int					mousepress(int button, int x, int y, t_env *e);
int					mouserelease(int button, int x, int y, t_env *e);
int					hook(t_env *e);
int					mousescroll(int button, int x, int y, t_env *e);

/*
**	Fonction de dessin dans l'image.
*/

void				put_point(t_env *e, int x, int y, int color);
void				zoom_in(t_env *e);
void				zoom_out(t_env *e);

/*
**	Fonction d'initialisation des fractals.
*/

void				ft_set_frac(int i, t_env *e);

/*
**		Multithread, flou & palettes.
*/

void				threading(t_env *e);
void				blur(t_env *e);
int					*color_tab(t_env *e);
int					color_m(t_env *e, int k, double tab[12]);
int					*update_tab(t_env *e);

#endif
