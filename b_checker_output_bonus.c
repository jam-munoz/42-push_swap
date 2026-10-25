/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_checker_output_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joamunoz <joamunoz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 00:00:00 by joamunoz          #+#    #+#             */
/*   Updated: 2026/10/25 00:00:00 by joamunoz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_checker_bonus.h"
#include <fcntl.h>

int	checker_mute_operations(void)
{
	int	saved_stdout;
	int	null_fd;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
		return (-1);
	null_fd = open("/dev/null", O_WRONLY);
	if (null_fd < 0)
	{
		close(saved_stdout);
		return (-1);
	}
	if (dup2(null_fd, STDOUT_FILENO) < 0)
	{
		close(null_fd);
		close(saved_stdout);
		return (-1);
	}
	close(null_fd);
	return (saved_stdout);
}

void	checker_restore_output(int saved_stdout)
{
	if (saved_stdout < 0)
		return ;
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdout);
}
