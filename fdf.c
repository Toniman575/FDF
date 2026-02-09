#include <mlx.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "libft/get_next_line/get_next_line.h"
#include "libft/libft.h"
#include "fdf.h"

int	setup_world(const char *file, t_world *world)
{
	int			fd;
	char		*line;
	
	fd = open(file, O_RDONLY);
	line = get_next_line_single(fd);
}

t_state	setup(const char *file)
{
	t_state		state;
	state.mlx.mlx_ptr = mlx_init();
	state.mlx.win_ptr = mlx_new_window(state.mlx.mlx_ptr, 500, 500, "FDF");
	state.image.img = mlx_new_image(state.mlx.mlx_ptr, 500, 500);
	state.image.addr = mlx_get_data_addr(state.image.img, &state.image.bits_per_pixel,
		&state.image.line_length,&state.image.endian);
	state.mlx.img = state.image;
	setup_world(file, &state.world);
}

int	main(int varc, char **argv) {
	t_state		state;
	t_image		img;
	t_mlx_data	mlx;


	if (varc != 2)
		return (0);
	state = setup(argv[1]);
	while (line)
	{
		char **row = ft_split(line, ' ');
		int i = 0;
		while (row[i])
		{
			ft_is
		}
	}
}


/*

void	my_mlx_pixel_put(t_image *data, int x, int y, int color) {
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	render(t_mlx_data *data)
{
	return (mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0));
}

mlx.mlx_ptr = mlx_init();
mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 500, 500, "Imagine");
img.img = mlx_new_image(mlx.mlx_ptr, 500, 500);
img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	&img.line_length,&img.endian);
mlx.img = img;

int x_start = 225;
int y_start = 225;
int size = 50;
for (int y = y_start; y < y_start + size; y++)
{
	for (int x = x_start; x < x_start + size; x++)
	{
		my_mlx_pixel_put(&mlx.img, x, y, 0x00FF0000);
	}
}
render(&mlx);
mlx_loop(mlx.mlx_ptr);
*/