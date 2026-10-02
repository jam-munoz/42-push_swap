#include "push_swap.h"

static void	alloc_error_exit(t_stack **stack, t_stack **arr, t_stack **tmp)
{
	free(arr);
	free(tmp);
	error_exit(stack);
}

static int	assign_index(t_stack **arr, int size)
{
	int	i;

	i = 0;
	size--;
	while (i < size)
	{
		if (arr[i]->number == arr[i + 1]->number)
			return (0);
		arr[i]->index = i;
		i++;
	}
	arr[i]->index = i;
	return (1);
}

static void	merge(t_stack **arr, t_stack **tmp, int left, int right)
{
	int	mid;
	int	i;
	int	j;
	int	k;

	mid = (left + right) / 2;
	i = left;
	j = mid + 1;
	k = left;
	while (i <= mid && j <= right)
	{
		if (arr[i]->number <= arr[j]->number)
			tmp[k++] = arr[i++];
		else
			tmp[k++] = arr[j++];
	}
	while (i <= mid)
		tmp[k++] = arr[i++];
	while (j <= right)
		tmp[k++] = arr[j++];
}

static void	merge_sort(t_stack **arr, t_stack **tmp, int left, int right)
{
	int	mid;
	int	i;

	if (left >= right)
		return ;
	mid = (left + right) / 2;
	merge_sort(arr, tmp, left, mid);
	merge_sort(arr, tmp, mid + 1, right);
	merge(arr, tmp, left, right);
	i = left;
	while (i <= right)
	{
		arr[i] = tmp[i];
		i++;
	}
}

void	index_stack(t_stack **stack, int size)
{
	t_stack	**arr;
	t_stack	**tmp;
	t_stack	*p;
	int		i;

	arr = malloc(size * sizeof(t_stack *));
	tmp = malloc(size * sizeof(t_stack *));
	if (arr == NULL || tmp == NULL)
		alloc_error_exit(stack, arr, tmp);
	i = 0;
	p = *stack;
	while (p != NULL)
	{
		arr[i++] = p;
		p = p->next;
	}
	merge_sort(arr, tmp, 0, size - 1);
	i = assign_index(arr, size);
	free(arr);
	free(tmp);
	if (i == 0)
		error_exit(stack);
}
