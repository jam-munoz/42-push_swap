/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 08:56:03 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/14 08:56:04 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static long	merge(t_stack **arr, t_stack **tmp, int left, int right)
{
	int		mid;
	int		i;
	int		j;
	long	inversions;

	mid = (left + right) / 2;
	i = left;
	j = mid + 1;
	inversions = 0;
	while (i <= mid && j <= right)
	{
		if (arr[i]->number <= arr[j]->number)
			tmp[left++] = arr[i++];
		else
		{
			tmp[left++] = arr[j++];
			inversions += mid - i + 1;
		}
	}
	while (i <= mid)
		tmp[left++] = arr[i++];
	while (j <= right)
		tmp[left++] = arr[j++];
	return (inversions);
}

static long	merge_sort(t_stack **arr, t_stack **tmp, int left, int right)
{
	int		mid;
	int		i;
	long	inversions;

	if (left >= right)
		return (0);
	mid = (left + right) / 2;
	inversions = merge_sort(arr, tmp, left, mid);
	inversions += merge_sort(arr, tmp, mid + 1, right);
	inversions += merge(arr, tmp, left, right);
	i = left;
	while (i <= right)
	{
		arr[i] = tmp[i];
		i++;
	}
	return (inversions);
}

long	index_stack(t_stack **stack, int size)
{
	t_stack	**arr;
	t_stack	**tmp;
	t_stack	*p;
	int		i;
	long	inversions;

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
	inversions = merge_sort(arr, tmp, 0, size - 1);
	i = assign_index(arr, size);
	free(arr);
	free(tmp);
	if (i == 0)
		error_exit(stack);
	return (inversions);
}
