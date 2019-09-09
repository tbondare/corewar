#include <stdio.h>

int main(int argc, char **argv)
{
	int i;
	int j;
	t_unic_num *frst;

	i = 0;
	j = 1;
	while (j <= argc)
	{
		if (ft_strequ(argv[j], "-n") == 1)
		{
			if (ft_isdigit(argv[++j][0]) == 1)
			{
				add_player_to_list(&frst);
				frst->unic_num = ft_atoi(argv[j]);
				read_player(argv[++j]);
			}
		}
		else

		j++;
	}
	return 0;
}