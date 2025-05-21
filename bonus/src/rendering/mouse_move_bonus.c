#include "../../includes/cub3d.h"

#define LEFT 0
#define RIGHT 1

int	mouse_move(int x, int y, void *param)
{
    t_cub *data;

    data = (t_cub *)param;
	(void)y;
    if (data->mouse_x == 0 && x != 0)
    {
        data->mouse_x = x;
        return (0);
    }
    data->mouse_times++;
	if (x > data->mouse_x && !(data->mouse_times % MOUSE_SPEED))
    {
        update_dir(data, RIGHT);
        ft_printf("%d\n", data->mouse_times);
    }
	else if (x < data->mouse_x && !(data->mouse_times % MOUSE_SPEED))
    {
        ft_printf("%d\n", data->mouse_times);
		update_dir(data, LEFT);
    }
	data->mouse_x = x;
	return (0);
}
