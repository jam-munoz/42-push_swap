
#include "push_swap.h"

int	num_count(char *str)
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

int	split_values(char *str, t_stack **stack_a, int **arr)
{
	int	numbers;
	int	i;

	numbers = num_count(str);
	*arr = malloc(numbers * sizeof(int));
	i = 0;
	while (i < numbers)
	{
		while (*str == ' ')
			str++;
		//adaptarlo a push back o armar array y despues copiar todo
		copy_data(str, stack_a, &(*arr)[i], *arr);
		while (*str && *str != ' ')
			str++;
		i++;
	}
	return (numbers);
}
