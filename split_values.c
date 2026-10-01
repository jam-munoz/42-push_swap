
#include "push_swap.h"

int num_count(char *str)
{
	int	numbers;

	numbers = 0;
	while (*str != '\0')
	{
		if (*str != ' ')
		{
			numbers++;
			while (*str && *str != ' ')
				str++;
		}
		else
			str++;
	}
	return numbers;
}

void split_values(char *str, t_stack **stack_a)
{
	int	numbers;
	int	i;

	numbers = num_count(str);
	i = 0;
	while (i < numbers)
	{
		while (*str == ' ')
			str++;
		copy_data(str, stack_a);
		while (*str && *str != ' ')
			str++;
		i++;
	}
	return ;
}
